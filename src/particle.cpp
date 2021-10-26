#include "particle.hpp"
#include "exception.hpp"
#include "math.hpp"
#include "camera.hpp"

// -------------------------------------------------------------------------- //

void TParticle::init()
{
    TObject::init();
}

// -------------------------------------------------------------------------- //

void TParticle::update()
{
    TObject::update();

    mMtxNeedsUpdate = true;
    mVelocity += mAcceleration;
    mPosition += mVelocity + mConfig->force;
    mPosition += mDirection;

    mFrame += kInterval / mConfig->lifeSpan;
    mScale.lerp(mConfig->scaleOverTime, mFrame * kInterval);
    mAlpha = TMath<u8>::lerp(mAlpha, mConfig->alphaOverTime, mFrame * kInterval);

    mIsExpired = mLifeTimer.update();
}

// -------------------------------------------------------------------------- //

void TParticle::draw()
{
    if (!mInCamera)
        return;

    if (mMtxNeedsUpdate)
        updateMtx();

    gSPMatrix(mDynList->pushDL(), OS_K0_TO_PHYSICAL(&mFMtx),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_PUSH);
    
    if (mConfig->type & EEmitType::EMIT_BILLBOARD) {
        gSPMatrix(mDynList->pushDL(), OS_K0_TO_PHYSICAL(TCamera::getFacingMtx()),
	    G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);
    }
    //gSPMatrix(mDynList->pushDL(), OS_K0_TO_PHYSICAL(&mFScaleMtx),
	//      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);
        
    if (mMesh != nullptr) {
        gDPSetPrimColor(mDynList->pushDL(), 0, 0, mInitColor.x(), mInitColor.y(), mInitColor.z(), mAlpha);
        gSPDisplayList(mDynList->pushDL(), mMesh);
    }

    gSPPopMatrix(mDynList->pushDL(), G_MTX_MODELVIEW);
}

// -------------------------------------------------------------------------- //

void TParticle::updateMtx()
{
    TObject::updateMtx();
}

// -------------------------------------------------------------------------- //

void TParticle::setConfig(TEmitConfig const & config)
{
    mLifeSpan = config.lifeSpan;
    mAcceleration = config.acceleration;
    mVelocity = config.velocity;
    mAlpha = config.alpha;

    mLifeTimer.start(config.lifeSpan);

    if (config.type & (EEmitType::EMIT_2D)) {
        mMesh = config.mesh2d;
    } else {
        mMesh = config.mesh3d;
    }

    if (mMesh == nullptr) {
        TException::fault("PTCL DL IS NULL!");
    }
    
    mInitColor = TVec3<u8>{TMath<u8>::random(0, 255), TMath<u8>::random(0, 255), TMath<u8>::random(0, 255)};

    mConfig = const_cast<TEmitConfig *>(&config);
}

// -------------------------------------------------------------------------- //