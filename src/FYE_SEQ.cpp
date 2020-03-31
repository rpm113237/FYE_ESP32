
#include <Arduino.h>
#include <seq_ESP32.h> 

SeqEntry seqList[NumSeqs];
Sequence_Step REDstep, IRstep;

void parse_exec_seq(int i){

     for (int j = 0; j <2; j++){
  Serial.printf("time since start (ms) = %lu\n",millis());  
//   seqList[i].
  string my_str = seqList[i].seqdetail;
	vector<string> result;

	stringstream s_stream(my_str); //create string stream from the string
	
	while(s_stream.good()){
    string substr;
		getline(s_stream, substr, ','); //get first string delimited by comma
  	result.push_back(substr);
	}
                                }
}      

uint16_t  get_num (vector<string> seq, int i) {      //gets the num--as in fx123
return atoi(seq.at(i).substr(2).c_str());
    
}

void defSeq(void){
int seq = 0;    
// SeqEntry seqList[NumSeqs];

// seqList[seq].seqnum = seq;
// seqList[seq].seqcomment ="hello";
seqList[0].seqname = "Face 1(facial two)";
seqList[0].seqdetail = "f1292,m1100,t120,b13,t120,b13,t120,b13,t120,b13,t114,b11,t17,b13,t121,b13,t119,b13,"  
"t13,b11,t116,b13,t120,b13,t117,b11,t12,b13,t121,b13,t13,f2292,t260,f1292,m1100,t16,b11,t143,b13,t122,b13,t111,b11,t16,b13,t120,b13,t120,b13,t15,b11,t115,"
"b13,t120,b13,t118,b11,t124,b13,t12,f2292,t260,f1292,m1100,t128,b13,t120,b13,t110,b13,t124,b11,t15,b13,t120,b13,t120,b13,t15,b11,t115,b13,t120,b13,t119,"
"b11,t11,b13,t120,b13,f2292,t260,f1292,m1100,t129,b13,t11,b11,t118,b13,t120,b13,t115,b11,t15,b13,t110,b13,t120,b13,t15,b11,t114,b13,t120,b13,t120,b13,"
"t120,b13,f2292,t260,";
seqList[0].seqcomment = "This is sequence zero--used to be Face 1 button";

seq = 1;
seqList[seq].seqnum = seq;
seqList[seq].seqname = "Face 2 (facial three)";
seqList[seq].seqdetail = "f173,m1100,t15,b13,t120,b13,t116,b11,t13,b13,t120,b13,t120,b13,t17,b11,t112,b13,t120,b13,t121,b13,t120,"
"b13,t120,b13,t112,b11,t17,b14,f273,t260,f1146,m1100,t16,b13,t120,b13,t117,b11,t120,b13,t120,b13,t120,b13,t19,b11,t111,b13,t120,b13,t120,b13,t120,b13,"
"t120,b13,t123,b11,t18,b13,f233,t260,f1584,m1100,t19,b11,t120,b13,t118,b11,t12,b13,t119,b13,t121,b13,t19,b11,t110,b13,t143,b13,t120,b13,t121,b13,t113,"
"b11,t16,b13,t120,b13,t120,b13,t15,b11,t16,f2584,t2300";
seqList[seq].seqcomment = "Used to be Face 2 button";

seq = 2;
seqList[seq].seqnum = seq;
seqList[seq].seqname = "Face 3(facial 4)";
seqList[seq].seqdetail = "F1146,T110,B11,T11,B16,T118,B13,T120,B13,T110,B11,T110,B13,T120,B13,T120,B13,t11,b11,T119,B13,T120,B13,T115,B13,"
"T115,B13,T120,B13,T19,F2146,F1284,T110,B13,T120,B13,T120,B13,T11,B11,T18,B13,T120,B13,T121,B13,T12,B11,T18,B13,T120,B13,T116,B11,T14,B13,T143,F2584,"
"T260,F11168,T16,B13,T120,B13,T120,B13,T11,B11,T17,B13,T121,B13,T120,B13,T11,B11,t117,b13,t120,b13,t117,b11,t13,b13,T120,B13,T121,B13,t17,b11,t113,b13,"
"T120,B13,t116,f2235,t2240";
seqList[seq].seqcomment = "Used to be Face 3";

seq = 3;
seqList[seq].seqnum = seq;
seqList[seq].seqname = "Hair 1 (hair 1)";
seqList[seq].seqdetail = "f173,m1100, t116,b13,t113,b13,t120,b13,t120,b13,t14,b11,t115,b13,t121,b13,t118,b13,"
"t12,b13,t120,b13,t120,b13,t19,b11,t120,b13,t115,b11,t16,f2292,t260,f1584,t113,b13,t114,b11,t15,b13,t120,b13,t120,b13,t16,b11,t114,"
"b13,t120,b13,t119,b11,t11,b11,t120,b13,t15,f2584, t2120,f12336,t110,b13,t115,b11,t14,b14,t121,b13,t120,b13,t17,b11,t112,b13,t120,"
"b13,t120,b13,t121,b13,t120,b13,t111,b11,t18,b11,t120,b13,t120,b13,t12,b11,t118,b13,t12,f273,t2300,";
seqList[seq].seqcomment = "Formerly hair one";

seq = 4;
seqList[seq].seqnum = seq;
seqList[seq].seqname = "Hair 2 (Nogier 1-Chronic)";
seqList[seq].seqdetail = "f173,m1100,t13,b13,t119,b13,t119,b11,t11,b13,t119,b13,t119,b13,"
"t19,b11,t110,b13,t120,b13,t119,b13,t11,b11,t117,b13,t120,b13,t120,b11,t11,b13,t119,b13,t120,b13,t17,b11,t19,f273,"
"t2300,f173,m1100,t17,b11,t120,b13,t120,b13,t120,b13,t120,b13,t112,b11,t17,b13,t19,b114,t120,b13,t14,b11,t116,b13,"
"t120,b13,t117,b11,t12,b13,t120,b13,t120,b13,t19,b11,t15,f2146,t2300";
seqList[seq].seqcomment = "Formerly Hair 2 button";

seq = 5;
seqList[seq].seqnum = seq;
seqList[seq].seqname = "Hair 3 (Nogier 2-Inflammation)";
seqList[seq].seqdetail = "f1146,m1100,t117,b13,t120,b13,t120,b13,t19,b11,t19,b13,"
"t120,b13,t120,b13,t13,b11,t116,b13,t120,b13,t117,b11,t12,b13,t120,b13,t117,b13,t17,b11,t135,b13,t11,f2146,t2300,f1146,m1100,t119,"
"b13,t120,b13,t121,b13,t113,b11,t16,b13,t120,b13,t120,b13,t15,b11,t114,b13,t123,b11,t118,b11,t11,b13,t120,b13,t120,b13,t18,"
"b11,t111,b13,t120,b13,f2146,t2300,";
seqList[seq].seqcomment = "Formerly Hair3 button";

seq = 6;
seqList[seq].seqnum = seq;
seqList[seq].seqname = "ALT1 Skin 3 4Feb15 RPM";
seqList[seq].seqdetail = "m1100,f1146,t16,b13,t116,b11,t13,b13,t120,b13,t120,b13,t120,f2292,t2180,f1584,t14,b13,t117,b11,t14,b13,"
"t120,b13,t120,b13,t18,b11,t133,f21168,t2180,f2236,t11,b13,t118,b11,t12,b11,t123,b13,t120,b13,f12336,t111,b13,t120,b13,t120,b13,t120,b13,"
"t120,b13,t114,b11,t16,b13,t120,b13,t120,b13,t16,b11,t115,b13,t120,f24672,t2300,";
seqList[seq].seqcomment = "Formerly Shift + Face 1";

seq = 7;
seqList[seq].seqnum = seq;
seqList[seq].seqname = "ALT2 Skin 3 ";
seqList[seq].seqdetail = "m1100,f1146,t16,b13,t116,b11,t13,b13,t120,b13,t120,b13,t120,f2292,t2180,f1584,t14,b13,t117,b11,t14,b13,"
"t120,b13,t120,b13,t18,b11,t133,f21168,t2180,f2236,t11,b13,t118,b11,t12,b11,t123,b13,t120,b13,f12336,t111,b13,t120,b13,t120,b13,t120,b13,t120,"
"b13,t114,b11,t16,b13,t120,b13,t120,b13,t16,b11,t115,b13,t120,f24672,t2300,";
seqList[seq].seqcomment = "Formerly Shift + Face 2";


seq = 8;
seqList[seq].seqnum = seq;
seqList[seq].seqname = "ALT3 Hair 2 (Nogier 1-Chronic)";
seqList[seq].seqdetail = "f173,m1100,t13,b13,t119,b13,t119,b11,t11,b13,t119,b13,t119,b13,t19,b11,t110,b13,t120,"
"b13,t119,b13,t11,b11,t117,b13,t120,b13,t120,b11,t11,b13,t119,b13,t120,b13,t17,b11,t19,f272,t2300,f173,m1100,t17,b11,t120,b13,t120,b13,t120,b13,"
"t120,b13,t112,b11,t17,b13,t19,b114,t120,b13,t14,b11,t116,b13,t120,b13,t117,b11,t12,b13,t120,b13,t120,b13,t19,b11,t15,f2146,t2300,";
seqList[seq].seqcomment = "Formerly shift + Face 3";

seq = 9;
seqList[seq].seqnum = seq;
seqList[seq].seqname = "ALT4 Hair 3 (Nogier 2-Inflammation)";
seqList[seq].seqdetail = "f1146,m1100,t117,b13,t120,b13,t120,b13,t19,b11,t19,b13,t120,b13,t120,b13,t13,b11,"
"t116,b13,t120,b13,t117,b11,t12,b13,t120,b13,t117,b13,t17,b11,t135,b13,t11,f2146,t2300,f1146,m1100,t119,b13,t120,b13,t121,b13,t113,b11,t16,b13,t120,"
"b13,t120,b13,t15,b11,t114,b13,t123,b11,t118,b11,t11,b13,t120,b13,t120,b13,t18,b11,t111,b13,t120,b13,f2146,t2300,";
seqList[seq].seqcomment = "Formerly shift pplus Hair1";

seq = 10;
seqList[seq].seqnum = seq;
seqList[seq].seqname = "ALT5 Relaxation, Feb17";
seqList[seq].seqdetail = "f19344,t112,b15,t13,t120,b13,t120,b17,t114,b13,t120,b13,t120,b13,t120,b13,t120,b13,t112,b13, t19,b13,t120,"
"b13,t120,b13,t120,b12,t18,b13,t121,b13,t17,f29344, t2300,f19344,t111,b11,b13,t120,b13,t120,b13,t18,b11,b13,t120,b13,t120,b13,t120,b13,t120,b13,t113,"
"b13,t17,b13,t121,b13,t120,b13,t13,b13,t120,b12,t19,t2300";
seqList[seq].seqcomment = "Formerly Shift + Hair2";

seq = 11;
seqList[seq].seqnum = seq;
seqList[seq].seqname = "ALT6 Wound, Feb17";
seqList[seq].seqdetail = "f1292, t18, b13,t114,b13,t16,b13,t120,b13,t120,b14,t16, b11,t115,b13,t120,b13,t119, b11,t11,b13,t120,b13,t120,b13,"
"b11,t111,b13,t120,b13,t120,b13,t12,b11,t131,f2292, t2300,f1292,t13,t15,b13,t116,b11,t14,b13,t120,b13,t120,b13,t17,b11,t113,b13,t120,b13,t120,b13,"
"t121,b13,t120,b13,t113,b11,t17,b13,t120, b13,t120,b13,t11, b11,t125,b13,f2292,t2300,";
seqList[seq].seqcomment = "Formerly Shift + Hair3";

seq = 12;
seqList[seq].seqnum = seq;
seqList[seq].seqname = "ALT7 2min 40hz Red_40 Hz IR";
seqList[seq].seqdetail = "f140, f240,b13, t1120, t2120,t1120, t2120,t1120, t2120,";
seqList[seq].seqcomment = "Alzheimers test, formerly a backdoor";

seq = 13;
seqList[seq].seqnum = seq;
seqList[seq].seqname = "30000 seconds 292Hz Red";
seqList[seq].seqdetail = "f1292,t130000,";
seqList[seq].seqcomment = "backdoor Red test";

seq = 14;
seqList[seq].seqnum = seq;
seqList[seq].seqname = "30000 seconds 292Hz IR";
seqList[seq].seqdetail = "f2292,t230000";
seqList[seq].seqcomment = "Backdoor IR test";

seq = 15;
seqList[seq].seqnum = seq;
seqList[seq].seqname = "Power stepping";
seqList[seq].seqdetail = "p1150,f1292,t130,p1160,t130,p1170, t130,p1180, t130,p1190,t130,p1200,t130,p1190,t130, p1180,t130, p1170,t130, p1160,t130, p1150,t130,";
seqList[seq].seqcomment = "empty";

seq = 16;
seqList[seq].seqnum = seq;
seqList[seq].seqname = "0123456789abcdefghijklmnopqrstuv";
seqList[seq].seqdetail = "empty";
seqList[seq].seqcomment = "empty";

seq = 17;
seqList[seq].seqnum = seq;
seqList[seq].seqname = "empty";
seqList[seq].seqdetail = "empty";
seqList[seq].seqcomment = "empty";

seq = 18;
seqList[seq].seqnum = seq;
seqList[seq].seqname = "empty";
seqList[seq].seqdetail = "empty";
seqList[seq].seqcomment = "empty";

seq = 19;
seqList[seq].seqnum = seq;
seqList[seq].seqname = "empty";
seqList[seq].seqdetail = "empty";
seqList[seq].seqcomment = "empty";


 




}

