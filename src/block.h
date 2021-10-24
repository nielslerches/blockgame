#pragma once

typedef struct BlockTexture
{
    const char *path;
} BlockTexture;

typedef struct Block
{
    BlockTexture texture;
} Block;

Block* new_block(BlockTexture);
