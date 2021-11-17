#include <nusys.h>

#include "math.hpp"
#include "staticobj.hpp"
#include "collider.hpp"

// -------------------------------------------------------------------------- //

class TPokeStop : 
    public TObject,
    public TSphereCollider
{
    public:

    TPokeStop(TDynList2 * dl) :
        TObject { dl }
    {
    }

    virtual ~TPokeStop() = default;

    virtual void init() override;
    virtual void update() override;
    virtual void draw() override;

    virtual void updateMtx() override;

    void setRadius(float radius) { mRadius = radius; setCollideRadius(radius); }
    float getRadius() {return mRadius;}

    protected:
    float mRadius{1000.0f};

    s16 mHeadRotation;
    s16 mPlatRotation;
    s16 mSwirlRotation;

    Mtx mFHeadMtx{};
    Mtx mFPlatMtx{};
    Mtx mFSwirlMtx{};

    Gfx * mHeadMesh;
    Gfx * mSwirlMesh;
    Gfx * mPlatMesh;

    virtual void onCollide(TCollider *) override;
};

// -------------------------------------------------------------------------- //