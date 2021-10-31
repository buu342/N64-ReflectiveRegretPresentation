#ifndef _PRESENTATION_MDL_CATHERINE_H
#define _PRESENTATION_MDL_CATHERINE_H

    #include "../helper.h"

    // Face macros
    #define TOTALFACES 3
    #define FACE_Catherine_default 0
    #define FACE_Catherine_neutral 1
    #define FACE_Catherine_gasp    2
    
    
    // Model convenience macro
    #define MODEL_Catherine (&mdl_Catherine)
    
    // Mesh data
    #define MESHCOUNT_Catherine         19
    #define MESH_Catherine_Pad          0
    #define MESH_Catherine_LeftForearm  1
    #define MESH_Catherine_LeftFemur    2
    #define MESH_Catherine_LeftLeg      3
    #define MESH_Catherine_LeftArm      4
    #define MESH_Catherine_RightFoot    5
    #define MESH_Catherine_LeftFoot     6
    #define MESH_Catherine_RightHand    7
    #define MESH_Catherine_Head         8
    #define MESH_Catherine_RightArm     9
    #define MESH_Catherine_Chest        10
    #define MESH_Catherine_RightForearm 11
    #define MESH_Catherine_RightFemur   12
    #define MESH_Catherine_Ponytail     13
    #define MESH_Catherine_Bang         14
    #define MESH_Catherine_Pelvis       15
    #define MESH_Catherine_Sword        16
    #define MESH_Catherine_RightLeg     17
    #define MESH_Catherine_LeftHand     18
    
    // Animation data
    #define ANIMATION_Catherine_Run    0
    #define ANIMATION_Catherine_Idle   1
    #define ANIMATION_Catherine_Broken 2
    
    extern s64ModelData mdl_Catherine;
    extern FaceAnim catherine_faces[TOTALFACES];

#endif