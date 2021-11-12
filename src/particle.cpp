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
    mVelocity += mAcceleration;
    mPosition += mVelocity + mConfig->force;
    mPosition += mDirection;

    mFrame += kInterval / mConfig->lifeSpan;
    mScale.lerp(mConfig->scaleOverTime, mFrame);
    mAlpha = TMath<u8>::lerp(mAlpha, mConfig->alphaOverTime, mFrame);

    mIsExpired = mLifeTimer.update();
}

// -------------------------------------------------------------------------- //

void TParticle::draw()
{
    updateMtx();    //Particle always needs to update its matrix

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
    TMtx44 temp1, mPosMtx, mScaleMtx;
    
    mPosMtx.translate(mPosition);
    mScaleMtx.scale(mScale);

    //Combine mtx
    TMtx44::concat(mPosMtx, mScaleMtx, temp1);

    TMtx44::floatToFixed(temp1, mFMtx);
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
    
    //mInitColor = TVec3<u8>{TMath<u8>::random(0, 255), TMath<u8>::random(0, 255), TMath<u8>::random(0, 255)};
    mInitColor = config.color;

    mConfig = const_cast<TEmitConfig *>(&config);
}

// -------------------------------------------------------------------------- //