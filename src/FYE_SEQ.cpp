
#include <Arduino.h>
#include <seq_ESP32.h> 

SeqEntry seqList[NumSeqs];

void defSeq(void){
int seq = 0;    
// SeqEntry seqList[NumSeqs];

// seqList[seq].seqnum = seq;
// seqList[seq].seqcomment ="hello";
seqList[0].seqname = "Face 1(facial two)4Feb15";
seqList[0].seqdetail = "f1292,m1100,t120,b13,t120,b13,t120,b13,t120,b13,t114,b11,t17,b13,t121,b13,t119,b13,"  
"t13,b11,t116,b13,t120,b13,t117,b11,t12,b13,t121,b13,t13,f2292,t260,f1292,m1100,t16,b11,t143,b13,t122,b13,t111,b11,t16,b13,t120,b13,t120,b13,t15,b11,t115,"
"b13,t120,b13,t118,b11,t124,b13,t12,f2292,t260,f1292,m1100,t128,b13,t120,b13,t110,b13,t124,b11,t15,b13,t120,b13,t120,b13,t15,b11,t115,b13,t120,b13,t119,"
"b11,t11,b13,t120,b13,f2292,t260,f1292,m1100,t129,b13,t11,b11,t118,b13,t120,b13,t115,b11,t15,b13,t110,b13,t120,b13,t15,b11,t114,b13,t120,b13,t120,b13,"
"t120,b13,f2292,t260,";
seqList[0].seqcomment = "This is sequence zero--used to be Face 1 button";

seq = 1;
seqList[seq].seqnum = seq;
seqList[seq].seqname = "Face 2 (facial three) 3Feb15";
seqList[seq].seqdetail = "f173,m1100,t15,b13,t120,b13,t116,b11,t13,b13,t120,b13,t120,b13,t17,b11,t112,b13,t120,b13,t121,b13,t120,"
"b13,t120,b13,t112,b11,t17,b14,f273,t260,f1146,m1100,t16,b13,t120,b13,t117,b11,t120,b13,t120,b13,t120,b13,t19,b11,t111,b13,t120,b13,t120,b13,t120,b13,"
"t120,b13,t123,b11,t18,b13,f233,t260,f1584,m1100,t19,b11,t120,b13,t118,b11,t12,b13,t119,b13,t121,b13,t19,b11,t110,b13,t143,b13,t120,b13,t121,b13,t113,"
"b11,t16,b13,t120,b13,t120,b13,t15,b11,t16,f2584,t2300";
seqList[seq].seqcomment = "Used to be Face 2 button";

seq = 2;
seqList[seq].seqnum = seq;
seqList[seq].seqname = "Face 3(facial 4) 6May15 RPM";
seqList[seq].seqdetail = "F1146,T110,B11,T11,B16,T118,B13,T120,B13,T110,B11,T110,B13,T120,B13,T120,B13,t11,b11,T119,B13,T120,B13,T115,B13,"
"T115,B13,T120,B13,T19,F2146,F1284,T110,B13,T120,B13,T120,B13,T11,B11,T18,B13,T120,B13,T121,B13,T12,B11,T18,B13,T120,B13,T116,B11,T14,B13,T143,F2584,"
"T260,F11168,T16,B13,T120,B13,T120,B13,T11,B11,T17,B13,T121,B13,T120,B13,T11,B11,t117,b13,t120,b13,t117,b11,t13,b13,T120,B13,T121,B13,t17,b11,t113,b13,"
"T120,B13,t116,f2235,t2240";
seqList[seq].seqcomment = "Used to be Face 3";

seq = 3;
seqList[seq].seqnum = seq;
seqList[seq].seqname = "Hair 1 (hair 1) 2Feb15_rpm";
seqList[seq].seqdetail = "f173,m1100, t116,b13,t113,b13,t120,b13,t120,b13,t14,b11,t115,b13,t121,b13,t118,b13,"
"t12,b13,t120,b13,t120,b13,t19,b11,t120,b13,t115,b11,t16,f2292,t260,f1584,t113,b13,t114,b11,t15,b13,t120,b13,t120,b13,t16,b11,t114,"
"b13,t120,b13,t119,b11,t11,b11,t120,b13,t15,f2584, t2120,f12336,t110,b13,t115,b11,t14,b14,t121,b13,t120,b13,t17,b11,t112,b13,t120,"
"b13,t120,b13,t121,b13,t120,b13,t111,b11,t18,b11,t120,b13,t120,b13,t12,b11,t118,b13,t12,f273,t2300,";
seqList[seq].seqcomment = "Formerly hair one";

seq = 4;
seqList[seq].seqnum = seq;
seqList[seq].seqname = "Hair 2 (Nogier 1-Chronic)2Feb15 10Oct16";
seqList[seq].seqdetail = "f173,m1100,t13,b13,t119,b13,t119,b11,t11,b13,t119,b13,t119,b13,"
"t19,b11,t110,b13,t120,b13,t119,b13,t11,b11,t117,b13,t120,b13,t120,b11,t11,b13,t119,b13,t120,b13,t17,b11,t19,f273,"
"t2300,f173,m1100,t17,b11,t120,b13,t120,b13,t120,b13,t120,b13,t112,b11,t17,b13,t19,b114,t120,b13,t14,b11,t116,b13,"
"t120,b13,t117,b11,t12,b13,t120,b13,t120,b13,t19,b11,t15,f2146,t2300";
seqList[seq].seqcomment = "Formerly Hair 2 button";

seq = 5;
seqList[seq].seqnum = seq;
seqList[seq].seqname = "Hair 3 (Nogier 2-Inflammation)2Feb15";
seqList[seq].seqdetail = "f1146,m1100,t117,b13,t120,b13,t120,b13,t19,b11,t19,b13,"
"t120,b13,t120,b13,t13,b11,t116,b13,t120,b13,t117,b11,t12,b13,t120,b13,t117,b13,t17,b11,t135,b13,t11,f2146,t2300,f1146,m1100,t119,"
"b13,t120,b13,t121,b13,t113,b11,t16,b13,t120,b13,t120,b13,t15,b11,t114,b13,t123,b11,t118,b11,t11,b13,t120,b13,t120,b13,t18,"
"b11,t111,b13,t120,b13,f2146,t2300,";
seqList[seq].seqcomment = "";

seq = 6;
seqList[seq].seqnum = seq;
seqList[seq].seqname = "ALT1 Skin 3 4Feb15 RPM";
seqList[seq].seqdetail = "m1100,f1146,t16,b13,t116,b11,t13,b13,t120,b13,t120,b13,t120,f2292,t2180,f1584,t14,b13,t117,b11,t14,b13,"
"t120,b13,t120,b13,t18,b11,t133,f21168,t2180,f2236,t11,b13,t118,b11,t12,b11,t123,b13,t120,b13,f12336,t111,b13,t120,b13,t120,b13,t120,b13,"
"t120,b13,t114,b11,t16,b13,t120,b13,t120,b13,t16,b11,t115,b13,t120,f24672,t2300,";
seqList[seq].seqcomment = "Formerly Shift + Face 1";

seq = 7;
seqList[seq].seqnum = seq;
seqList[seq].seqname = "nALT2 Skin 3 HPwr 4Feb15 RPM";
seqList[seq].seqdetail = "m1100,f1146,t16,b13,t116,b11,t13,b13,t120,b13,t120,b13,t120,f2292,t2180,f1584,t14,b13,t117,b11,t14,b13,"
"t120,b13,t120,b13,t18,b11,t133,f21168,t2180,f2236,t11,b13,t118,b11,t12,b11,t123,b13,t120,b13,f12336,t111,b13,t120,b13,t120,b13,t120,b13,t120,"
"b13,t114,b11,t16,b13,t120,b13,t120,b13,t16,b11,t115,b13,t120,f24672,t2300,";
seqList[seq].seqcomment = "Formerly Shift + Face 2";


seq = 8;
seqList[seq].seqnum = seq;
seqList[seq].seqname = "";
seqList[seq].seqdetail = "";
seqList[seq].seqcomment = "";

seq = 9;
seqList[seq].seqnum = seq;
seqList[seq].seqname = "";
seqList[seq].seqdetail = "";
seqList[seq].seqcomment = "";

seq = 10;
seqList[seq].seqnum = seq;
seqList[seq].seqname = "";
seqList[seq].seqdetail = "";
seqList[seq].seqcomment = "";

seq = 11;
seqList[seq].seqnum = seq;
seqList[seq].seqname = "";
seqList[seq].seqdetail = "";
seqList[seq].seqcomment = "";

seq = 12;
seqList[seq].seqnum = seq;
seqList[seq].seqname = "";
seqList[seq].seqdetail = "";
seqList[seq].seqcomment = "";

seq = 13;
seqList[seq].seqnum = seq;
seqList[seq].seqname = "";
seqList[seq].seqdetail = "";
seqList[seq].seqcomment = "";

seq = 14;
seqList[seq].seqnum = seq;
seqList[seq].seqname = "";
seqList[seq].seqdetail = "";
seqList[seq].seqcomment = "";

seq = 15;
seqList[seq].seqnum = seq;
seqList[seq].seqname = "";
seqList[seq].seqdetail = "";
seqList[seq].seqcomment = "";

seq = 16;
seqList[seq].seqnum = seq;
seqList[seq].seqname = "";
seqList[seq].seqdetail = "";
seqList[seq].seqcomment = "";

seq = 17;
seqList[seq].seqnum = seq;
seqList[seq].seqname = "";
seqList[seq].seqdetail = "";
seqList[seq].seqcomment = "";

seq = 18;
seqList[seq].seqnum = seq;
seqList[seq].seqname = "";
seqList[seq].seqdetail = "";
seqList[seq].seqcomment = "";

seq = 19;
seqList[seq].seqnum = seq;
seqList[seq].seqname = "";
seqList[seq].seqdetail = "";
seqList[seq].seqcomment = "";


 
/* const char* sequences[] = {


"nALT2 Skin 3 HPwr 4Feb15 RPM,",

"nALT3 Hair 2 (Nogier 1-Chronic) HPwr 2Feb15,f173,m1100,t13,b13,t119,b13,t119,b11,t11,b13,t119,b13,t119,b13,t19,b11,t110,b13,t120,"
"b13,t119,b13,t11,b11,t117,b13,t120,b13,t120,b11,t11,b13,t119,b13,t120,b13,t17,b11,t19,f272,t2300,f173,m1100,t17,b11,t120,b13,t120,b13,t120,b13,"
"t120,b13,t112,b11,t17,b13,t19,b114,t120,b13,t14,b11,t116,b13,t120,b13,t117,b11,t12,b13,t120,b13,t120,b13,t19,b11,t15,f2146,t2300,",

"nALT4 Hair 3 (Nogier 2-Inflammation)2Feb15 HPwr ,f1146,m1100,t117,b13,t120,b13,t120,b13,t19,b11,t19,b13,t120,b13,t120,b13,t13,b11,"
"t116,b13,t120,b13,t117,b11,t12,b13,t120,b13,t117,b13,t17,b11,t135,b13,t11,f2146,t2300,f1146,m1100,t119,b13,t120,b13,t121,b13,t113,b11,t16,b13,t120,"
"b13,t120,b13,t15,b11,t114,b13,t123,b11,t118,b11,t11,b13,t120,b13,t120,b13,t18,b11,t111,b13,t120,b13,f2146,t2300,",

"nALT5 Relaxation, Feb17,f19344, t112,b15,t13,t120,b13,t120,b17,t114,b13,t120,b13,t120,b13,t120,b13,t120,b13,t112,b13, t19,b13,t120,"
"b13,t120,b13,t120,b12,t18,b13,t121,b13,t17,f29344, t2300,f19344,t111,b11,b13,t120,b13,t120,b13,t18,b11,b13,t120,b13,t120,b13,t120,b13,t120,b13,t113,"
"b13,t17,b13,t121,b13,t120,b13,t13,b13,t120,b12,t19,t2300,",

"nALT6 Wound, Feb17,  f1292, t18, b13,t114,b13,t16,b13,t120,b13,t120,b14,t16, b11,t115,b13,t120,b13,t119, b11,t11,b13,t120,b13,t120,b13,"
"b11,t111,b13,t120,b13,t120,b13,t12,b11,t131,f2292, t2300,f1292,t13,t15,b13,t116,b11,t14,b13,t120,b13,t120,b13,t17,b11,t113,b13,t120,b13,t120,b13,"
"t121,b13,t120,b13,t113,b11,t17,b13,t120, b13,t120,b13,t11, b11,t125,b13,f2292,t2300,",

"nALT7 2min 40hz Red_40 Hz IR twelve min total,f140, f240,b13, t1120, t2120,t1120, t2120,t1120, t2120,",

"n30000seconds 292Hz Red,f1292,t130000,",

"n30000seconds 292Hz IR,f2292,t230000,",

"nPower stepping,p1150,f1292,t130,p1160,t130,p1170, t130,p1180, t130,p1190,t130,p1200,t130,p1190,t130, p1180,t130, p1170,t130, p1160,t130, p1150,t130,",

"nDocumentation string. Here goes description of sequences, etc." 

};

 */



}
