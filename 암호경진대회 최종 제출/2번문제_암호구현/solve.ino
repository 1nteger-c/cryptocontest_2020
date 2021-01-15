#pragma GCC optimize ("-O3") 
#define ROUND_NUM 128
typedef unsigned char u8; 
typedef unsigned short u16;

u8 ROL8(u8 x, u8 n) {
return ((u8) ((x) << (n)) | (u8) ((x) >> (8 - (n))));
}

u16 ROL16(u16 x, u16 n) {
return ((u16) ((x) << (n)) | (u16) ((x) >> (16 - (n))));
}

void key_gen(u8 *rnd, u8 *key) { 
u8 key_in[2];
u8 tmp1, tmp2; 
u16 *key_p;
u16 con = 0x9ABC;
key_in[0] = key[0]; 
key_in[1] = key[1];
key_p = (u16*) key_in;
int i = 0;
static u8 R_BOX1[256] = {0, 34, 68, 102, 136, 170, 204, 238, 17, 51, 85, 119, 153, 187, 221, 255, 34, 68, 102, 136, 170, 204, 238, 16, 51, 85, 119, 153, 187, 221, 255, 33, 68, 102, 136, 170, 204, 238, 16, 50, 85, 119, 153, 187, 221, 255, 33, 67, 102, 136, 170, 204, 238, 16, 50, 84, 119, 153, 187, 221, 255, 33, 67, 101, 136, 170, 204, 238, 16, 50, 84, 118, 153, 187, 221, 255, 33, 67, 101, 135, 170, 204, 238, 16, 50, 84, 118, 152, 187, 221, 255, 33, 67, 101, 135, 169, 204, 238, 16, 50, 84, 118, 152, 186, 221, 255, 33, 67, 101, 135, 169, 203, 238, 16, 50, 84, 118, 152, 186, 220, 255, 33, 67, 101, 135, 169, 203, 237, 17, 51, 85, 119, 153, 187, 221, 255, 34, 68, 102, 136, 170, 204, 238, 16, 51, 85, 119, 153, 187, 221, 255, 33, 68, 102, 136, 170, 204, 238, 16, 50, 85, 119, 153, 187, 221, 255, 33, 67, 102, 136, 170, 204, 238, 16, 50, 84, 119, 153, 187, 221, 255, 33, 67, 101, 136, 170, 204, 238, 16, 50, 84, 118, 153, 187, 221, 255, 33, 67, 101, 135, 170, 204, 238, 16, 50, 84, 118, 152, 187, 221, 255, 33, 67, 101, 135, 169, 204, 238, 16, 50, 84, 118, 152, 186, 221, 255, 33, 67, 101, 135, 169, 203, 238, 16, 50, 84, 118, 152, 186, 220, 255, 33, 67, 101, 135, 169, 203, 237, 16, 50, 84, 118, 152, 186, 220, 254};
static u8 R_BOX2[256] = {0, 136, 17, 153, 34, 170, 51, 187, 68, 204, 85, 221, 102, 238, 119, 255, 136, 16, 153, 33, 170, 50, 187, 67, 204, 84, 221, 101, 238, 118, 255, 135, 17, 153, 34, 170, 51, 187, 68, 204, 85, 221, 102, 238, 119, 255, 136, 16, 153, 33, 170, 50, 187, 67, 204, 84, 221, 101, 238, 118, 255, 135, 16, 152, 34, 170, 51, 187, 68, 204, 85, 221, 102, 238, 119, 255, 136, 16, 153, 33, 170, 50, 187, 67, 204, 84, 221, 101, 238, 118, 255, 135, 16, 152, 33, 169, 51, 187, 68, 204, 85, 221, 102, 238, 119, 255, 136, 16, 153, 33, 170, 50, 187, 67, 204, 84, 221, 101, 238, 118, 255, 135, 16, 152, 33, 169, 50, 186, 68, 204, 85, 221, 102, 238, 119, 255, 136, 16, 153, 33, 170, 50, 187, 67, 204, 84, 221, 101, 238, 118, 255, 135, 16, 152, 33, 169, 50, 186, 67, 203, 85, 221, 102, 238, 119, 255, 136, 16, 153, 33, 170, 50, 187, 67, 204, 84, 221, 101, 238, 118, 255, 135, 16, 152, 33, 169, 50, 186, 67, 203, 84, 220, 102, 238, 119, 255, 136, 16, 153, 33, 170, 50, 187, 67, 204, 84, 221, 101, 238, 118, 255, 135, 16, 152, 33, 169, 50, 186, 67, 203, 84, 220, 101, 237, 119, 255, 136, 16, 153, 33, 170, 50, 187, 67, 204, 84, 221, 101, 238, 118, 255, 135, 16, 152, 33, 169, 50, 186, 67, 203, 84, 220, 101, 237, 118, 254};
static u16 R_BOX3[256] = {0, 514, 1028, 1542, 2056, 2570, 3084, 3598, 4112, 4626, 5140, 5654, 6168, 6682, 7196, 7710, 8224, 8738, 9252, 9766, 10280, 10794, 11308, 11822, 12336, 12850, 13364, 13878, 14392, 14906, 15420, 15934, 16448, 16962, 17476, 17990, 18504, 19018, 19532, 20046, 20560, 21074, 21588, 22102, 22616, 23130, 23644, 24158, 24672, 25186, 25700, 26214, 26728, 27242, 27756, 28270, 28784, 29298, 29812, 30326, 30840, 31354, 31868, 32382, 32896, 33410, 33924, 34438, 34952, 35466, 35980, 36494, 37008, 37522, 38036, 38550, 39064, 39578, 40092, 40606, 41120, 41634, 42148, 42662, 43176, 43690, 44204, 44718, 45232, 45746, 46260, 46774, 47288, 47802, 48316, 48830, 49344, 49858, 50372, 50886, 51400, 51914, 52428, 52942, 53456, 53970, 54484, 54998, 55512, 56026, 56540, 57054, 57568, 58082, 58596, 59110, 59624, 60138, 60652, 61166, 61680, 62194, 62708, 63222, 63736, 64250, 64764, 65278, 257, 771, 1285, 1799, 2313, 2827, 3341, 3855, 4369, 4883, 5397, 5911, 6425, 6939, 7453, 7967, 8481, 8995, 9509, 10023, 10537, 11051, 11565, 12079, 12593, 13107, 13621, 14135, 14649, 15163, 15677, 16191, 16705, 17219, 17733, 18247, 18761, 19275, 19789, 20303, 20817, 21331, 21845, 22359, 22873, 23387, 23901, 24415, 24929, 25443, 25957, 26471, 26985, 27499, 28013, 28527, 29041, 29555, 30069, 30583, 31097, 31611, 32125, 32639, 33153, 33667, 34181, 34695, 35209, 35723, 36237, 36751, 37265, 37779, 38293, 38807, 39321, 39835, 40349, 40863, 41377, 41891, 42405, 42919, 43433, 43947, 44461, 44975, 45489, 46003, 46517, 47031, 47545, 48059, 48573, 49087, 49601, 50115, 50629, 51143, 51657, 52171, 52685, 53199, 53713, 54227, 54741, 55255, 55769, 56283, 56797, 57311, 57825, 58339, 58853, 59367, 59881, 60395, 60909, 61423, 61937, 62451, 62965, 63479, 63993, 64507, 65021, 65535};
while(i<ROUND_NUM){
    tmp1 = R_BOX1[key_in[0]] + R_BOX2[key_in[1]];
    tmp2 = R_BOX1[key_in[0]] ^ R_BOX2[key_in[1]];
    key_in[0] = tmp1;
    key_in[1] = tmp2;
    rnd[i * 2 + 0] = key_in[0];
    rnd[i * 2 + 1] = key_in[1];
    i ++;

    *key_p = R_BOX3[key_in[0]] + R_BOX3[key_in[1]] + 0x3579;
    tmp1 = key_in[0] + key_in[1];
    tmp2 = key_in[0] ^ key_in[1];
    key_in[0] = tmp1;
    key_in[1] = tmp2;
    rnd[i * 2 + 0] = key_in[0];
    rnd[i * 2 + 1] = key_in[1];
    i++;

    tmp1 = R_BOX1[key_in[0]] + R_BOX2[key_in[1]];
    tmp2 = R_BOX1[key_in[0]] ^ R_BOX2[key_in[1]];
    key_in[0] = tmp1;
    key_in[1] = tmp2;
    rnd[i * 2 + 0] = key_in[0];
    rnd[i * 2 + 1] = key_in[1];
    i ++;

    *key_p = R_BOX3[key_in[0]] + R_BOX3[key_in[1]] + 0xd5e4;
    tmp1 = key_in[0] + key_in[1];
    tmp2 = key_in[0] ^ key_in[1];
    key_in[0] = tmp1;
    key_in[1] = tmp2;
    rnd[i * 2 + 0] = key_in[0];
    rnd[i * 2 + 1] = key_in[1];
    i++;

    tmp1 = R_BOX1[key_in[0]] + R_BOX2[key_in[1]];
    tmp2 = R_BOX1[key_in[0]] ^ R_BOX2[key_in[1]];
    key_in[0] = tmp1;
    key_in[1] = tmp2;
    rnd[i * 2 + 0] = key_in[0];
    rnd[i * 2 + 1] = key_in[1];
    i ++;

    *key_p = R_BOX3[key_in[0]] + R_BOX3[key_in[1]] + 0x5793;
    tmp1 = key_in[0] + key_in[1];
    tmp2 = key_in[0] ^ key_in[1];
    key_in[0] = tmp1;
    key_in[1] = tmp2;
    rnd[i * 2 + 0] = key_in[0];
    rnd[i * 2 + 1] = key_in[1];
    i++;

    tmp1 = R_BOX1[key_in[0]] + R_BOX2[key_in[1]];
    tmp2 = R_BOX1[key_in[0]] ^ R_BOX2[key_in[1]];
    key_in[0] = tmp1;
    key_in[1] = tmp2;
    rnd[i * 2 + 0] = key_in[0];
    rnd[i * 2 + 1] = key_in[1];
    i ++;

    *key_p = R_BOX3[key_in[0]] + R_BOX3[key_in[1]] + 0x5e4d;
    tmp1 = key_in[0] + key_in[1];
    tmp2 = key_in[0] ^ key_in[1];
    key_in[0] = tmp1;
    key_in[1] = tmp2;
    rnd[i * 2 + 0] = key_in[0];
    rnd[i * 2 + 1] = key_in[1];
    i++;


    tmp1 = R_BOX1[key_in[0]] + R_BOX2[key_in[1]];
    tmp2 = R_BOX1[key_in[0]] ^ R_BOX2[key_in[1]];
    key_in[0] = tmp1;
    key_in[1] = tmp2;
    rnd[i * 2 + 0] = key_in[0];
    rnd[i * 2 + 1] = key_in[1];
    i ++;

    *key_p = R_BOX3[key_in[0]] + R_BOX3[key_in[1]] + 0x7935;
    tmp1 = key_in[0] + key_in[1];
    tmp2 = key_in[0] ^ key_in[1];
    key_in[0] = tmp1;
    key_in[1] = tmp2;
    rnd[i * 2 + 0] = key_in[0];
    rnd[i * 2 + 1] = key_in[1];
    i++;

    tmp1 = R_BOX1[key_in[0]] + R_BOX2[key_in[1]];
    tmp2 = R_BOX1[key_in[0]] ^ R_BOX2[key_in[1]];
    key_in[0] = tmp1;
    key_in[1] = tmp2;
    rnd[i * 2 + 0] = key_in[0];
    rnd[i * 2 + 1] = key_in[1];
    i ++;

    *key_p = R_BOX3[key_in[0]] + R_BOX3[key_in[1]] + 0xe4d5;
    tmp1 = key_in[0] + key_in[1];
    tmp2 = key_in[0] ^ key_in[1];
    key_in[0] = tmp1;
    key_in[1] = tmp2;
    rnd[i * 2 + 0] = key_in[0];
    rnd[i * 2 + 1] = key_in[1];
    i++;
    tmp1 = R_BOX1[key_in[0]] + R_BOX2[key_in[1]];
    tmp2 = R_BOX1[key_in[0]] ^ R_BOX2[key_in[1]];
    key_in[0] = tmp1;
    key_in[1] = tmp2;
    rnd[i * 2 + 0] = key_in[0];
    rnd[i * 2 + 1] = key_in[1];
    i ++;

    *key_p = R_BOX3[key_in[0]] + R_BOX3[key_in[1]] + 0x9357;
    tmp1 = key_in[0] + key_in[1];
    tmp2 = key_in[0] ^ key_in[1];
    key_in[0] = tmp1;
    key_in[1] = tmp2;
    rnd[i * 2 + 0] = key_in[0];
    rnd[i * 2 + 1] = key_in[1];
    i++;

    tmp1 = R_BOX1[key_in[0]] + R_BOX2[key_in[1]];
    tmp2 = R_BOX1[key_in[0]] ^ R_BOX2[key_in[1]];
    key_in[0] = tmp1;
    key_in[1] = tmp2;
    rnd[i * 2 + 0] = key_in[0];
    rnd[i * 2 + 1] = key_in[1];
    i ++;

    *key_p = R_BOX3[key_in[0]] + R_BOX3[key_in[1]] + 0x4d5e;
    rnd[i * 2 + 0] = key_in[0] + key_in[1];
    rnd[i * 2 + 1] = key_in[0] ^ key_in[1];
    key_in[0] = rnd[i * 2 + 0];
    key_in[1] = rnd[i * 2 + 1];
    i++;

    tmp1 = R_BOX1[key_in[0]] + R_BOX2[key_in[1]];
    tmp2 = R_BOX1[key_in[0]] ^ R_BOX2[key_in[1]];
    key_in[0] = tmp1;
    key_in[1] = tmp2;
    rnd[i * 2 + 0] = key_in[0];
    rnd[i * 2 + 1] = key_in[1];
    i ++;

    *key_p = R_BOX3[key_in[0]] + R_BOX3[key_in[1]] + 0x3579;
    tmp1 = key_in[0] + key_in[1];
    tmp2 = key_in[0] ^ key_in[1];
    key_in[0] = tmp1;
    key_in[1] = tmp2;
    rnd[i * 2 + 0] = key_in[0];
    rnd[i * 2 + 1] = key_in[1];
    i++;

    tmp1 = R_BOX1[key_in[0]] + R_BOX2[key_in[1]];
    tmp2 = R_BOX1[key_in[0]] ^ R_BOX2[key_in[1]];
    key_in[0] = tmp1;
    key_in[1] = tmp2;
    rnd[i * 2 + 0] = key_in[0];
    rnd[i * 2 + 1] = key_in[1];
    i ++;

    *key_p = R_BOX3[key_in[0]] + R_BOX3[key_in[1]] + 0xd5e4;
    tmp1 = key_in[0] + key_in[1];
    tmp2 = key_in[0] ^ key_in[1];
    key_in[0] = tmp1;
    key_in[1] = tmp2;
    rnd[i * 2 + 0] = key_in[0];
    rnd[i * 2 + 1] = key_in[1];
    i++;

    tmp1 = R_BOX1[key_in[0]] + R_BOX2[key_in[1]];
    tmp2 = R_BOX1[key_in[0]] ^ R_BOX2[key_in[1]];
    key_in[0] = tmp1;
    key_in[1] = tmp2;
    rnd[i * 2 + 0] = key_in[0];
    rnd[i * 2 + 1] = key_in[1];
    i ++;

    *key_p = R_BOX3[key_in[0]] + R_BOX3[key_in[1]] + 0x5793;
    tmp1 = key_in[0] + key_in[1];
    tmp2 = key_in[0] ^ key_in[1];
    key_in[0] = tmp1;
    key_in[1] = tmp2;
    rnd[i * 2 + 0] = key_in[0];
    rnd[i * 2 + 1] = key_in[1];
    i++;

    tmp1 = R_BOX1[key_in[0]] + R_BOX2[key_in[1]];
    tmp2 = R_BOX1[key_in[0]] ^ R_BOX2[key_in[1]];
    key_in[0] = tmp1;
    key_in[1] = tmp2;
    rnd[i * 2 + 0] = key_in[0];
    rnd[i * 2 + 1] = key_in[1];
    i ++;

    *key_p = R_BOX3[key_in[0]] + R_BOX3[key_in[1]] + 0x5e4d;
    tmp1 = key_in[0] + key_in[1];
    tmp2 = key_in[0] ^ key_in[1];
    key_in[0] = tmp1;
    key_in[1] = tmp2;
    rnd[i * 2 + 0] = key_in[0];
    rnd[i * 2 + 1] = key_in[1];
    i++;


    tmp1 = R_BOX1[key_in[0]] + R_BOX2[key_in[1]];
    tmp2 = R_BOX1[key_in[0]] ^ R_BOX2[key_in[1]];
    key_in[0] = tmp1;
    key_in[1] = tmp2;
    rnd[i * 2 + 0] = key_in[0];
    rnd[i * 2 + 1] = key_in[1];
    i ++;

    *key_p = R_BOX3[key_in[0]] + R_BOX3[key_in[1]] + 0x7935;
    tmp1 = key_in[0] + key_in[1];
    tmp2 = key_in[0] ^ key_in[1];
    key_in[0] = tmp1;
    key_in[1] = tmp2;
    rnd[i * 2 + 0] = key_in[0];
    rnd[i * 2 + 1] = key_in[1];
    i++;

    tmp1 = R_BOX1[key_in[0]] + R_BOX2[key_in[1]];
    tmp2 = R_BOX1[key_in[0]] ^ R_BOX2[key_in[1]];
    key_in[0] = tmp1;
    key_in[1] = tmp2;
    rnd[i * 2 + 0] = key_in[0];
    rnd[i * 2 + 1] = key_in[1];
    i ++;

    *key_p = R_BOX3[key_in[0]] + R_BOX3[key_in[1]] + 0xe4d5;
    tmp1 = key_in[0] + key_in[1];
    tmp2 = key_in[0] ^ key_in[1];
    key_in[0] = tmp1;
    key_in[1] = tmp2;
    rnd[i * 2 + 0] = key_in[0];
    rnd[i * 2 + 1] = key_in[1];
    i++;
    tmp1 = R_BOX1[key_in[0]] + R_BOX2[key_in[1]];
    tmp2 = R_BOX1[key_in[0]] ^ R_BOX2[key_in[1]];
    key_in[0] = tmp1;
    key_in[1] = tmp2;
    rnd[i * 2 + 0] = key_in[0];
    rnd[i * 2 + 1] = key_in[1];
    i ++;

    *key_p = R_BOX3[key_in[0]] + R_BOX3[key_in[1]] + 0x9357;
    tmp1 = key_in[0] + key_in[1];
    tmp2 = key_in[0] ^ key_in[1];
    key_in[0] = tmp1;
    key_in[1] = tmp2;
    rnd[i * 2 + 0] = key_in[0];
    rnd[i * 2 + 1] = key_in[1];
    i++;

    tmp1 = R_BOX1[key_in[0]] + R_BOX2[key_in[1]];
    tmp2 = R_BOX1[key_in[0]] ^ R_BOX2[key_in[1]];
    key_in[0] = tmp1;
    key_in[1] = tmp2;
    rnd[i * 2 + 0] = key_in[0];
    rnd[i * 2 + 1] = key_in[1];
    i ++;

    *key_p = R_BOX3[key_in[0]] + R_BOX3[key_in[1]] + 0x4d5e;
    rnd[i * 2 + 0] = key_in[0] + key_in[1];
    rnd[i * 2 + 1] = key_in[0] ^ key_in[1];
    key_in[0] = rnd[i * 2 + 0];
    key_in[1] = rnd[i * 2 + 1];
    i++;
}
} 


void enc(u8 *text, u8 *rnd) {
  u8 text_in[2];
  u8 tmp;
  u8 a1,a2;
  u16 *text_p;

  text_in[0] = text[0];
  text_in[1] = text[1];

  text_p = (u16*) text_in;

  int i = 0;
  while (i < ROUND_NUM) {
    *text_p = ROL16(*text_p, 4);
    text_in[0] = text_in[0] + rnd[i * 2 + 0];
    text_in[1] = text_in[1] ^ rnd[i * 2 + 1];
    i++;
    
    *text_p = ROL16(*text_p, 8);
    text_in[0] = text_in[0] + rnd[i * 2 + 0];
    text_in[1] = text_in[1] ^ rnd[i * 2 + 1];
    i++;

    *text_p = ROL16(*text_p, 4);
    text_in[0] = text_in[0] + rnd[i * 2 + 0];
    text_in[1] = text_in[1] ^ rnd[i * 2 + 1];
    i++;
  
    *text_p = ROL16(*text_p, 8);
    text_in[0] = text_in[0] + rnd[i * 2 + 0];
    text_in[1] = text_in[1] ^ rnd[i * 2 + 1];
    i++;

    *text_p = ROL16(*text_p, 4);
    text_in[0] = text_in[0] + rnd[i * 2 + 0];
    text_in[1] = text_in[1] ^ rnd[i * 2 + 1];
    i++;
  
    *text_p = ROL16(*text_p, 8);
    text_in[0] = text_in[0] + rnd[i * 2 + 0];
    text_in[1] = text_in[1] ^ rnd[i * 2 + 1];
    i++;

    *text_p = ROL16(*text_p, 4);
    text_in[0] = text_in[0] + rnd[i * 2 + 0];
    text_in[1] = text_in[1] ^ rnd[i * 2 + 1];
    i++;
  
    *text_p = ROL16(*text_p, 8);
    text_in[0] = text_in[0] + rnd[i * 2 + 0];
    text_in[1] = text_in[1] ^ rnd[i * 2 + 1];
    i++;

    *text_p = ROL16(*text_p, 4);
    text_in[0] = text_in[0] + rnd[i * 2 + 0];
    text_in[1] = text_in[1] ^ rnd[i * 2 + 1];
    i++;
  
    *text_p = ROL16(*text_p, 8);
    text_in[0] = text_in[0] + rnd[i * 2 + 0];
    text_in[1] = text_in[1] ^ rnd[i * 2 + 1];
    i++;

    *text_p = ROL16(*text_p, 4);
    text_in[0] = text_in[0] + rnd[i * 2 + 0];
    text_in[1] = text_in[1] ^ rnd[i * 2 + 1];
    i++;
  
    *text_p = ROL16(*text_p, 8);
    text_in[0] = text_in[0] + rnd[i * 2 + 0];
    text_in[1] = text_in[1] ^ rnd[i * 2 + 1];
    i++;

    *text_p = ROL16(*text_p, 4);
    text_in[0] = text_in[0] + rnd[i * 2 + 0];
    text_in[1] = text_in[1] ^ rnd[i * 2 + 1];
    i++;
  
    *text_p = ROL16(*text_p, 8);
    text_in[0] = text_in[0] + rnd[i * 2 + 0];
    text_in[1] = text_in[1] ^ rnd[i * 2 + 1];
    i++;

    *text_p = ROL16(*text_p, 4);
    text_in[0] = text_in[0] + rnd[i * 2 + 0];
    text_in[1] = text_in[1] ^ rnd[i * 2 + 1];
    i++;
  
    *text_p = ROL16(*text_p, 8);
    text_in[0] = text_in[0] + rnd[i * 2 + 0];
    text_in[1] = text_in[1] ^ rnd[i * 2 + 1];
    i++;

    *text_p = ROL16(*text_p, 4);
    text_in[0] = text_in[0] + rnd[i * 2 + 0];
    text_in[1] = text_in[1] ^ rnd[i * 2 + 1];
    i++;
  
    *text_p = ROL16(*text_p, 8);
    text_in[0] = text_in[0] + rnd[i * 2 + 0];
    text_in[1] = text_in[1] ^ rnd[i * 2 + 1];
    i++;

    *text_p = ROL16(*text_p, 4);
    text_in[0] = text_in[0] + rnd[i * 2 + 0];
    text_in[1] = text_in[1] ^ rnd[i * 2 + 1];
    i++;
  
    *text_p = ROL16(*text_p, 8);
    text_in[0] = text_in[0] + rnd[i * 2 + 0];
    text_in[1] = text_in[1] ^ rnd[i * 2 + 1];
    i++;

    *text_p = ROL16(*text_p, 4);
    text_in[0] = text_in[0] + rnd[i * 2 + 0];
    text_in[1] = text_in[1] ^ rnd[i * 2 + 1];
    i++;
  
    *text_p = ROL16(*text_p, 8);
    text_in[0] = text_in[0] + rnd[i * 2 + 0];
    text_in[1] = text_in[1] ^ rnd[i * 2 + 1];
    i++;

    *text_p = ROL16(*text_p, 4);
    text_in[0] = text_in[0] + rnd[i * 2 + 0];
    text_in[1] = text_in[1] ^ rnd[i * 2 + 1];
    i++;
  
    *text_p = ROL16(*text_p, 8);
    text_in[0] = text_in[0] + rnd[i * 2 + 0];
    text_in[1] = text_in[1] ^ rnd[i * 2 + 1];
    i++;

    *text_p = ROL16(*text_p, 4);
    text_in[0] = text_in[0] + rnd[i * 2 + 0];
    text_in[1] = text_in[1] ^ rnd[i * 2 + 1];
    i++;
    
    *text_p = ROL16(*text_p, 8);
    text_in[0] = text_in[0] + rnd[i * 2 + 0];
    text_in[1] = text_in[1] ^ rnd[i * 2 + 1];
    i++;

    *text_p = ROL16(*text_p, 4);
    text_in[0] = text_in[0] + rnd[i * 2 + 0];
    text_in[1] = text_in[1] ^ rnd[i * 2 + 1];
    i++;
    
    *text_p = ROL16(*text_p, 8);
    text_in[0] = text_in[0] + rnd[i * 2 + 0];
    text_in[1] = text_in[1] ^ rnd[i * 2 + 1];
    i++;

    *text_p = ROL16(*text_p, 4);
    text_in[0] = text_in[0] + rnd[i * 2 + 0];
    text_in[1] = text_in[1] ^ rnd[i * 2 + 1];
    i++;
    
    *text_p = ROL16(*text_p, 8);
    text_in[0] = text_in[0] + rnd[i * 2 + 0];
    text_in[1] = text_in[1] ^ rnd[i * 2 + 1];
    i++;

    *text_p = ROL16(*text_p, 4);
    text_in[0] = text_in[0] + rnd[i * 2 + 0];
    text_in[1] = text_in[1] ^ rnd[i * 2 + 1];
    i++;
    
    *text_p = ROL16(*text_p, 8);
    text_in[0] = text_in[0] + rnd[i * 2 + 0];
    text_in[1] = text_in[1] ^ rnd[i * 2 + 1];
    i++;
    
  }
  text[0] = text_in[0];
  text[1] = text_in[1];
}
u8 TEST_VECTOR(u8 *in, u8 *answer) {
return (in[0] == answer[0] && in[1] == answer[1]);
}

void setup() { Serial.begin(115200);
pinMode(LED_BUILTIN, OUTPUT);
u8 key[3][2] = { {0x12, 0x34}, {0x9A, 0xBD}, {0x11, 0x22} }; 
u8 rnd[ROUND_NUM * 2] = { 0, };
u8 text[3][2] = { {0x56, 0x78}, {0xDE, 0xF0}, {0x33, 0x44} }; 
u8 out_text[3][2] = { {0x50, 0x3F}, {0x88, 0x28}, {0x7F, 0x33} };
Serial.println("-----------------"); 
Serial.println(" TEST VECTOR ");
Serial.println("-----------------");
for(int i=0; i<3; i++) { key_gen(rnd, key[i]); 
enc(text[i], rnd);
if(TEST_VECTOR(text[i], out_text[i])){ 
Serial.println(">> CORRECT");
}else{
Serial.println(">> WRONG");
} }
Serial.println("-----------------"); 
Serial.println(" BENCHMARK "); 
Serial.println("-----------------");
u8 key_bench[2] = { 0x12, 0x34 }; 
u8 text_bench[2] = { 0x56, 0x78 };
u32 time1;
u32 time2;
time1 = millis();
for(int i=0; i<4096; i++) {
key_gen(rnd,key_bench);
enc(text_bench,rnd); 

    if (text_bench[0] > 0x80) {
      digitalWrite(LED_BUILTIN, HIGH);
    } else {
      digitalWrite(LED_BUILTIN, LOW);
    }

}
time2 = millis();
Serial.print(">> "); 
Serial.println((time2-time1)); Serial.println("-----------------");
}
void loop() { }
