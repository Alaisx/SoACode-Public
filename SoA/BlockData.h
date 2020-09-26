#pragma once
#include "stdafx.h"

#include <SDL2/SDL.h>
#include <Vorb/io/Keg.h>
#include <Vorb/graphics/ImageIO.h>
#include <Vorb/voxel/VoxCommon.h>

#include "CAEngine.h"
#include "ChunkMesh.h"
#include "BlockTexture.h"
#include "Constants.h"
#include "Item.h"

#define GETFLAGS(a) ((a) >> 12)
#define GETFLAG1(a) (((a) & 0x8000) >> 15)
#define GETFLAG2(a) (((a) & 0x4000) >> 14)
#define GETFLAG3(a) (((a) & 0x2000) >> 13)
#define GETFLAG4(a) (((a) & 0x1000) >> 12)
#define GETBLOCKID(a) (((a) & 0x0FFF))
#define SETFLAGS(a, b) ((a) = ((a) | ((b) << 12)))

enum class BlockOcclusion {
    NONE,
    ALL,
    SELF,
    SELF_ONLY
};
KEG_ENUM_DECL(BlockOcclusion);

class BlockTextureFaces {
public:
    union {
        ui32 array[6]; /// Access 6-sided block textures as an array
        class {
        public:
            ui32 nx;  /// Negative x-axis texture
            ui32 px;  /// Positive x-axis texture
            ui32 ny;  /// Negative y-axis texture
            ui32 py;  /// Positive y-axis texture
            ui32 nz;  /// Negative z-axis texture
            ui32 pz;  /// Positive z-axis texture
        }; /// Textures named in cardinal convention
    };
    
    ui32& operator[] (const i32& i) {
        return array[i];
    }
    const ui32& operator[] (const i32& i) const {
        return array[i];
    }
};

typedef nString BlockIdentifier; ///< Unique identifier key for blocks

typedef ui16 BlockID;

class Block
{
public:
    Block();

    void SetAvgTexColors();

    i32 temp;

    BlockIdentifier sID;
    nString name;
    BlockID ID;
    nString burnTransformID;
    i16 waveEffect;
    ui16 lightColorPacked; /// 5 bit RGB light color packed into a ui16
    i16 waterMeshLevel;
    i16 floatingAction;
    nString spawnerID;
    nString sinkID;
    ui16 explosionRays;
    ui16 floraHeight = 0;
    ui16 liquidStartID = 0;
    ui16 liquidLevels = 0;

    BlockOcclusion occlude;

    MeshType meshType;

    GLfloat moveMod;
    GLfloat explosionResistance;
    GLfloat explosivePower;
    GLfloat flammability;
    GLfloat explosionPowerLoss;
    f32v3 colorFilter;

    int caIndex = -1;
    CAAlgorithm caAlg = CAAlgorithm::NONE;
    nString caFilePath = "";

    ColorRGB8 lightColor;
    ui8 particleTex;
    bool powderMove;
    bool collide;
    bool waterBreak;
    bool blockLight;
    bool useable;
    bool allowLight;
    bool isCrushable;
    bool isSupportive;
    bool active;

    union {
        struct {
            BlockTexture* textureLeft;
            BlockTexture* textureRight;
            BlockTexture* textureBottom;
            BlockTexture* textureTop;
            BlockTexture* textureBack;
            BlockTexture* textureFront;
        };
        BlockTexture* textures[6];
    };

    // TODO(Ben): NOPE
    //                      ... but why?
    nString particleTexName;
    nString emitterName, emitterOnBreakName, emitterRandomName;
    class ParticleEmitter *emitter, *emitterOnBreak, *emitterRandom;

    std::vector <ColorRGB8> altColors;
};
KEG_TYPE_DECL(Block);

