//
//  game_settings.h
//  Mycraft
//
//  Created by Clapeysron on 14/11/2017.
//  Copyright © 2017 Clapeysron. All rights reserved.
//

#ifndef game_settings_h
#define game_settings_h

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define QUAD_SIZE 48
#define QUAD_FACE_SIZE 8
#define VERTEX_SIZE 8

//transparent material or model (MSB = 1)
#define AIR 0x80
#define WATER 0x81
#define LEAF 0x82

//non-transparent material (MSB = 0)
#define BOUND 0x00
#define ROCK 0x01
#define SOIL 0x02
#define GRASSLAND 0x03
#define TRUNK 0x04

//for hisrotyPath & adjVisibility
#define UP 0x20
#define DOWN 0x10
#define FRONT 0x08
#define BEHIND 0x04
#define LEFT 0x02
#define RIGHT 0x01
#define ALL_DIR 0x3f
#define NO_DIR 0x00

#define SOIL_THICKNESS 5

//index of vertices array
#define XNEG 0x00
#define XPOS 0x01
#define ZNEG 0x02
#define ZPOS 0x03
#define YNEG 0x04
#define YPOS 0x05

//vector reverse size
#define VECTOR_OFFSET 24576

//visible region radius (TO DO: 16)
#define RADIUS 3

//texture place
#define ROCK_X 0.3f
#define ROCK_Y 0.0f
#define SOIL_X 0.1f
#define SOIL_Y 0.0f
#define GRASSLAND_TOP_X 0.0f
#define GRASSLAND_TOP_Y 0.0f
#define GRASSLAND_SIDE_X 0.1f
#define GRASSLAND_SIDE_Y 0.0f

#define TRUNK 0x04

#endif /* game_settings_h */