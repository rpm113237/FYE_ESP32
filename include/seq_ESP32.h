/* 
 * File:   SeqFile.h
 * Author: Rich
 *
 * Created on January 11, 2017, 11:55 AM
 */

/* 
 * Created on August 28, 2015, 4:16 PM
 * Modified on 14Jul16 by RPM
 * New design needs lower power range:  by 1.9/2.6 = 0.73
 * Lost the base/emitter drop =.6 +/-
 * px200= px145; px254 = px188 
 * Modified again 8Feb16.  Changed order of ALT 1-3; added Relaxation & Wound.
 * Added ALT7 to ten seconds Red followed by ten seconds IR--for testing.
 * 28Jan2019--added t2300 to end of "Relaxation"
 */
/* 24Mar2020: ported to ESP_32 Project; git hereafter
*/

#ifndef SEQUENCES_H
#define	SEQUENCES_H
/*This is old bulk200
 * must have 15 entries--unless hard coded otherwise
 * Sequences is an array of pointers to string literals
 * 9Nov2017--changed sequence to not call out power.  they all use px200, the power can be adjusted
 */
//#include <string.h>
// string type array;

//  extern struct SeqEntry seqlist[20];
//  seqlist[0].

using namespace std;

#include<string>

#define NumSeqs 20      //max number of sequences

void defSeq(void);

struct SeqEntry {
  int seqnum;     
  std::string seqname; //human name--i.e Relaxation
  std::string seqdetail; //the sequence
  std::string seqcomment;  //any comment
  };

//extern SeqEntry seqList[NumSeqs];
// extern SeqEntry seqList [NumSeqs];
  
/* const char* sequences[] = {"nFace 1(facial two)4Feb15,f1292,m1100,t120,b13,t120,b13,t120,b13,t120,b13,t114,b11,t17,b13,t121,b13,t119,b13,"  //can I comment here? 
"t13,b11,t116,b13,t120,b13,t117,b11,t12,b13,t121,b13,t13,f2292,t260,f1292,m1100,t16,b11,t143,b13,t122,b13,t111,b11,t16,b13,t120,b13,t120,b13,t15,b11,t115,"
"b13,t120,b13,t118,b11,t124,b13,t12,f2292,t260,f1292,m1100,t128,b13,t120,b13,t110,b13,t124,b11,t15,b13,t120,b13,t120,b13,t15,b11,t115,b13,t120,b13,t119,"
"b11,t11,b13,t120,b13,f2292,t260,f1292,m1100,t129,b13,t11,b11,t118,b13,t120,b13,t115,b11,t15,b13,t110,b13,t120,b13,t15,b11,t114,b13,t120,b13,t120,b13,"
"t120,b13,f2292,t260,",

"nFace 2 (facial three) 3Feb15,f173,m1100,t15,b13,t120,b13,t116,b11,t13,b13,t120,b13,t120,b13,t17,b11,t112,b13,t120,b13,t121,b13,t120,"
"b13,t120,b13,t112,b11,t17,b14,f273,t260,f1146,m1100,t16,b13,t120,b13,t117,b11,t120,b13,t120,b13,t120,b13,t19,b11,t111,b13,t120,b13,t120,b13,t120,b13,"
"t120,b13,t123,b11,t18,b13,f233,t260,f1584,m1100,t19,b11,t120,b13,t118,b11,t12,b13,t119,b13,t121,b13,t19,b11,t110,b13,t143,b13,t120,b13,t121,b13,t113,"
"b11,t16,b13,t120,b13,t120,b13,t15,b11,t16,f2584,t2300,",

"nFace 3(facial 4) 6May15 RPM,F1146,T110,B11,T11,B16,T118,B13,T120,B13,T110,B11,T110,B13,T120,B13,T120,B13,t11,b11,T119,B13,T120,B13,T115,B13,"
"T115,B13,T120,B13,T19,F2146,F1284,T110,B13,T120,B13,T120,B13,T11,B11,T18,B13,T120,B13,T121,B13,T12,B11,T18,B13,T120,B13,T116,B11,T14,B13,T143,F2584,"
"T260,F11168,T16,B13,T120,B13,T120,B13,T11,B11,T17,B13,T121,B13,T120,B13,T11,B11,t117,b13,t120,b13,t117,b11,t13,b13,T120,B13,T121,B13,t17,b11,t113,b13,"
"T120,B13,t116,f2235,t2240,",

"nHair 1 (hair 1) 2Feb15_rpm,f173,m1100, t116,b13,t113,b13,t120,b13,t120,b13,t14,b11,t115,b13,t121,b13,t118,b13,"
"t12,b13,t120,b13,t120,b13,t19,b11,t120,b13,t115,b11,t16,f2292,t260,f1584,t113,b13,t114,b11,t15,b13,t120,b13,t120,b13,t16,b11,t114,"
"b13,t120,b13,t119,b11,t11,b11,t120,b13,t15,f2584, t2120,f12336,t110,b13,t115,b11,t14,b14,t121,b13,t120,b13,t17,b11,t112,b13,t120,"
"b13,t120,b13,t121,b13,t120,b13,t111,b11,t18,b11,t120,b13,t120,b13,t12,b11,t118,b13,t12,f273,t2300,",

"nHair 2 (Nogier 1-Chronic)2Feb15 10Oct16,f173,m1100,t13,b13,t119,b13,t119,b11,t11,b13,t119,b13,t119,b13,"
"t19,b11,t110,b13,t120,b13,t119,b13,t11,b11,t117,b13,t120,b13,t120,b11,t11,b13,t119,b13,t120,b13,t17,b11,t19,f273,"
"t2300,f173,m1100,t17,b11,t120,b13,t120,b13,t120,b13,t120,b13,t112,b11,t17,b13,t19,b114,t120,b13,t14,b11,t116,b13,"
"t120,b13,t117,b11,t12,b13,t120,b13,t120,b13,t19,b11,t15,f2146,t2300,",

"nHair 3 (Nogier 2-Inflammation)2Feb15,f1146,m1100,t117,b13,t120,b13,t120,b13,t19,b11,t19,b13,"
"t120,b13,t120,b13,t13,b11,t116,b13,t120,b13,t117,b11,t12,b13,t120,b13,t117,b13,t17,b11,t135,b13,t11,f2146,t2300,f1146,m1100,t119,"
"b13,t120,b13,t121,b13,t113,b11,t16,b13,t120,b13,t120,b13,t15,b11,t114,b13,t123,b11,t118,b11,t11,b13,t120,b13,t120,b13,t18,"
"b11,t111,b13,t120,b13,f2146,t2300,",

"nALT1 Skin 3 4Feb15 RPM,m1100,f1146,t16,b13,t116,b11,t13,b13,t120,b13,t120,b13,t120,f2292,t2180,f1584,t14,b13,t117,b11,t14,b13,"
"t120,b13,t120,b13,t18,b11,t133,f21168,t2180,f2236,t11,b13,t118,b11,t12,b11,t123,b13,t120,b13,f12336,t111,b13,t120,b13,t120,b13,t120,b13,"
"t120,b13,t114,b11,t16,b13,t120,b13,t120,b13,t16,b11,t115,b13,t120,f24672,t2300,",

"nALT2 Skin 3 HPwr 4Feb15 RPM,m1100,f1146,t16,b13,t116,b11,t13,b13,t120,b13,t120,b13,t120,f2292,t2180,f1584,t14,b13,t117,b11,t14,b13,"
"t120,b13,t120,b13,t18,b11,t133,f21168,t2180,f2236,t11,b13,t118,b11,t12,b11,t123,b13,t120,b13,f12336,t111,b13,t120,b13,t120,b13,t120,b13,t120,"
"b13,t114,b11,t16,b13,t120,b13,t120,b13,t16,b11,t115,b13,t120,f24672,t2300,",

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
#endif	/* SEQUENCES_H */


