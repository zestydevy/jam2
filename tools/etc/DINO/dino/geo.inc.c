#include "src/game/envfx_snow.h"

const GeoLayout mario_geo[] = {
	
	
		mJoint->attachJoint(NULL, NULL, TVec3F{0.0F, 0.0F, 0.0F}, TVec3S{TSine::fromDeg(0.0F), TSine::fromDeg(0.0F), TSine::fromDeg(90.0F)});
		
			mJoint->attachAnimatedJoint(NULL, dino_Bone_mesh_layer_1, TVec3F{0.0F, 0.0F, 0.0F});
			
				gSPDisplayList(mDynList->pushDL(), dino_Bone_001_skinned_mesh_layer_1);
				mJoint->attachJoint(NULL, NULL, TVec3F{10.0F, 33.0F, 1.0F}, TVec3S{TSine::fromDeg(0.0F), TSine::fromDeg(0.0F), TSine::fromDeg(-90.0F)});
				
					mJoint->attachAnimatedJoint(NULL, dino_Bone_001_mesh_layer_1, TVec3F{0.0F, 0.0F, 0.0F});
					
						gSPDisplayList(mDynList->pushDL(), dino_Bone_002_skinned_mesh_layer_1);
						mJoint->attachAnimatedJoint(NULL, dino_Bone_002_mesh_layer_1, TVec3F{-22.0F, 25.0F, 0.0F});
						
							gSPDisplayList(mDynList->pushDL(), dino_Bone_002_mesh_layer_4);
						mJoint->detach();
					mJoint->detach();
				mJoint->detach();
				gSPDisplayList(mDynList->pushDL(), dino_foot_002_L_skinned_mesh_layer_1);
				mJoint->attachJoint(NULL, NULL, TVec3F{-21.0F, -2.0F, 12.0F}, TVec3S{TSine::fromDeg(-90.0F), TSine::fromDeg(0.0F), TSine::fromDeg(-90.0F)});
				
					mJoint->attachAnimatedJoint(NULL, dino_foot_002_L_mesh_layer_1, TVec3F{0.0F, 0.0F, 0.0F});
					
						gSPDisplayList(mDynList->pushDL(), dino_foot_L_skinned_mesh_layer_1);
						mJoint->attachJoint(NULL, NULL, TVec3F{0.0F, -11.0F, 7.0F}, TVec3S{TSine::fromDeg(16.0F), TSine::fromDeg(-115.0F), TSine::fromDeg(31.0F)});
						
							mJoint->attachAnimatedJoint(NULL, NULL, TVec3F{0.0F, 0.0F, 0.0F});
							
								mJoint->attachJoint(NULL, NULL, TVec3F{4.0F, -12.0F, -1.0F}, TVec3S{TSine::fromDeg(180.0F), TSine::fromDeg(29.0F), TSine::fromDeg(-55.0F)});
								
									mJoint->attachAnimatedJoint(NULL, dino_foot_L_mesh_layer_1, TVec3F{0.0F, 0.0F, 0.0F});
								mJoint->detach();
							mJoint->detach();
						mJoint->detach();
					mJoint->detach();
				mJoint->detach();
				gSPDisplayList(mDynList->pushDL(), dino_foot_002_R_skinned_mesh_layer_1);
				mJoint->attachJoint(NULL, NULL, TVec3F{-22.0F, -2.0F, -10.0F}, TVec3S{TSine::fromDeg(-90.0F), TSine::fromDeg(0.0F), TSine::fromDeg(-90.0F)});
				
					mJoint->attachAnimatedJoint(NULL, dino_foot_002_R_mesh_layer_1, TVec3F{0.0F, 0.0F, 0.0F});
					
						gSPDisplayList(mDynList->pushDL(), dino_foot_001_R_skinned_mesh_layer_1);
						mJoint->attachJoint(NULL, NULL, TVec3F{0.0F, -11.0F, 7.0F}, TVec3S{TSine::fromDeg(-35.0F), TSine::fromDeg(0.0F), TSine::fromDeg(0.0F)});
						
							mJoint->attachAnimatedJoint(NULL, dino_foot_001_R_mesh_layer_1, TVec3F{0.0F, 0.0F, 0.0F});
							
								gSPDisplayList(mDynList->pushDL(), dino_foot_R_skinned_mesh_layer_1);
								mJoint->attachJoint(NULL, NULL, TVec3F{1.0F, -12.0F, 4.0F}, TVec3S{TSine::fromDeg(0.0F), TSine::fromDeg(90.0F), TSine::fromDeg(125.0F)});
								
									mJoint->attachAnimatedJoint(NULL, dino_foot_R_mesh_layer_1, TVec3F{0.0F, 0.0F, 0.0F});
								mJoint->detach();
							mJoint->detach();
						mJoint->detach();
					mJoint->detach();
				mJoint->detach();
			mJoint->detach();
		mJoint->detach();
		gSPDisplayList(mDynList->pushDL(), dino_material_revert_render_settings);
		gSPDisplayList(mDynList->pushDL(), dino_material_revert_render_settings);
	mJoint->detach();
	GEO_END(),
};
