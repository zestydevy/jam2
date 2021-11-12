#include "emitter.hpp"
#include "heap.hpp"
#include "exception.hpp"
#include "particle.hpp"
#include "linklist.hpp"
#include "camera.hpp"

// -------------------------------------------------------------------------- //
extern int sParticleCnt;
TEmitter::TEmitter(TVec3<f32> const & position, TEmitConfig const & config, TDynList2 * dl)
{
    mPosition = position;
    mConfig = const_cast<TEmitConfig *>(&config);
    mPtclList.setHeap(THeap::getCurrentHeap());
    mCallbacks.setHeap(THeap::getCurrentHeap());
    mDl = dl;
    
    if (mConfig == NULL) {
        TException::fault("WARNING!! ptcl config is null...");
    }

    TParticle * ptcl = new TParticle(dl, config);
    ptcl->setPosition(position);
    ptcl->setScale(config.scale);
    mPtclList.push(ptcl);
    sParticleCnt++;
}

// -------------------------------------------------------------------------- //

void TEmitter::emit()
{
    if (mParent != nullptr) {
        mPosition = mParent->getPosition() + mParentOffset;
    }

    mInCamera = mAlwaysDraw || TCamera::checkVisible(mPosition, mDrawDistanceSquared);
    if (!mInCamera){
        return;
    }
    
    for (int i = 0; i < mPtclList.capacity(); ++i) {
        mPtclList[i]->update();
        if (mPtclList[i]->isExpired()) {
            delete mPtclList[i];
            mPtclList.erase(mPtclList.begin() + i);
            mPtclList.shrink();
            --sParticleCnt;
        }
    }
    
    // rate time is up
    if (mRateTimer.update())
    {
        TVec3F up{0.0f, 1.0f, 0.0f};
        TVec3F forward{TMath<f32>::frand(-1.0f, 1.0f), 0.0f, TMath<f32>::frand(-1.0f, 1.0f)};
        TVec3F right{TVec3<f32>(-forward.z(), 0.0f, forward.x())};
        TVec3F direction = forward + right;
        TParticle * ptcl = new TParticle(mDl, reinterpret_cast<TEmitConfig const & >(*mConfig));

        ptcl->setPosition(mPosition);
        ptcl->setScale(mConfig->scale);
        //ptcl->setDirection(direction);

        mPtclList.push(ptcl);
        mRateTimer.start(mConfig->lifeSpan * mConfig->rate);

        sParticleCnt++;
    } else {

    }
}

// -------------------------------------------------------------------------- //

void TEmitter::draw()
{
    if (!mInCamera){
        return;
    }

    if (mConfig->initDP){
        gSPDisplayList(mDl->pushDL(), mConfig->initDP);
    }
    for (int i = 0; i < mPtclList.capacity(); ++i) {
        mPtclList[i]->draw();
    }
    if (mConfig->cleanupDP){
        gSPDisplayList(mDl->pushDL(), mConfig->cleanupDP);
    }
}

// -------------------------------------------------------------------------- //

void TEmitter::destroy()
{
    // destroy all the particles allocated
    for (int i = 0; i < mPtclList.capacity(); ++i) {
        delete mPtclList[i];
    }
    
    // clear callbacks
    mCallbacks.clear();
}

// -------------------------------------------------------------------------- //

void TEmitter::attach(TObject * const object, TVec3F const & offset)
{
    mParent = const_cast<TObject *>(object);
    mPosition = object->getPosition();
    mParentOffset = offset;
}

// -------------------------------------------------------------------------- //

void TEmitter::attachCallback(void(*callback)())
{
    if (mCallbacks.capacity() > kMaxCallbacks) {
        TException::fault("TOO MANY CALLBACKS ATTACHED TO EMITTER");
    }
    mCallbacks.push(callback);
}

// -------------------------------------------------------------------------- //

void TEmitter::setParentOffset(TVec3F const & offset)
{
    mParentOffset = offset;
}

// -------------------------------------------------------------------------- //