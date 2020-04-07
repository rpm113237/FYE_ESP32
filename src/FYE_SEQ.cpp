
#include <Arduino.h>
#include <seq_ESP32.h> 

SeqEntry seqList[NumSeqs];
Stage_Spec seq_step[2];
Parse_Return p_ret;
unsigned int numbersequences;


int parse_exec_seq(int seq_Num, int seq_step_num ){    //TODO fix this.  Needs to load Seq up with RED/IR
//return step number--unless end--returns 0

  /*
parses seqList(seq_Num) starting at step_no.  The "action tags" are 
tnx and bnx--where  n is the color and x is the time.
when a "t" or "b" is found, the Seq_Spec struc seq_step[] is loaded with type (blink or run)
color (RED or IR) and time (seconds); parse_exec_seq exits with Color as return.
If end of sequennce, exits with OX00.  No color means end


  */

//  for (int j = 0; j <=numbersequences; j++){ 
  // Serial.printf("\n\ntime since start (ms) = %lu\n",millis());  
  // cout << "sequence number  = "<<j << " name = "<<seqList[j].seqname <<endl;
  // string my_str = seqList[j].seqdetail;
  // my_str.erase(remove(my_str.begin(), my_str.end(),' '),my_str.end());    //removes extra spaces.
  

  char tst_chr;
  int retval=-1;
	string my_str = seqList[seq_Num].seqdetail;
  my_str.erase(remove(my_str.begin(), my_str.end(),' '),my_str.end());    //removes extra spaces.
  vector<string> seq_cmd;
	stringstream s_stream(my_str); //create string stream from the string
	
	while(s_stream.good()){   //vectorize the sequence selected (seq_Num)
    string substr;
		getline(s_stream, substr, ','); 
  	seq_cmd.push_back(substr);
	}
 
 cout<<"how many entries in vector?  "<<seq_cmd.size() << endl;

 // seq_cmd is a vector of strings--each of which is a command
 //we are going to start with the seq_step entry
retval = -1;     //stay until we get an exit cmd (b or t)
while ((retval<0) && (seq_step_num < seq_cmd.size())){
    if (seq_cmd.at(seq_step_num).size() <=0) retval = 0;    //should be end of string
    if(seq_cmd.at(seq_step_num).size() >0){     //avoid problems with a null sequence (,, or trailing comma)
      cout <<"\nseq_cmd = "<<seq_cmd.at(seq_step_num) <<"\tseq step num = "<<seq_step_num<<endl;
      uint16_t param = get_num (seq_cmd, seq_step_num);     //returns zero if bad freq or num      
      int16_t sclr = get_clr (seq_cmd, seq_step_num);    //returns neg if bad color; otherwise 0= RED; 1 = IR
      tst_chr = 'x';  //default invalid
      if ((param >0) & (sclr>=0)) tst_chr = tolower(seq_cmd.at(seq_step_num)[0]);  //valid freq and color
      seq_step_num++;
      cout << "cmd = "  << tst_chr << "\tparam = "  << param << "\tcolor = "  << sclr << endl;
      switch (tst_chr) {

        case 'f':
          // cout<< "freq set cmd; freq =  "<< param << " color = " << sclr<< endl;
          seq_step[sclr].step_freq = param;          
          break;

        case 'p':
          // cout<< "It is a power cmd; power =  "<< param << " color = " << sclr<< endl;
          seq_step[sclr].step_power = param;          
          break;

        case 'm':
          // cout<< "Blink time in ms =  "<< param << " color = " << sclr<< endl;
          seq_step[sclr].blink_ms = param;          
          break;  

        case 'b':
        case 't':
          // cout<< "It is a time cmd; time =  "<< param << " secs; color = " << sclr<< endl;
          seq_step[sclr].step_secs = param;  //// redundant--in p_ret struct???
          p_ret.is_blink = false;
          if (tst_chr == 'b'){
           p_ret.is_blink = true;
           p_ret.out_freq = 0 ;     //blink defined by "m"
          } 
          p_ret.out_time = param;
          p_ret.out_color = sclr;
          p_ret.out_freq = param;  
          out_p_ret();
          retval = seq_step_num;  //been incremented
          break;  

        default:
          cout <<"not legal " << tst_chr << endl;
          retval = seq_step_num;
          break; 


                      } //end switch
    
		
                                      } // end >0 if

  delay(100);

} //end while (retval<0)

// while(1);
// cout <<"retval = " << retval <<endl;
  return retval;

                                 
}    

void out_p_ret(void){   //debug utility to output details

cout <<"Step spec summary: is it a blink?  " <<p_ret.is_blink;
cout <<"\t time = " << p_ret.out_time;
cout << "\t color  = "<< p_ret.out_color;
cout << "\t frequency = " << p_ret.out_freq << endl;




}

int16_t  get_num (vector<string> seq, int i) {      //gets the num--as in fx123
return atoi(seq.at(i).substr(2).c_str());           //returns zero if invalid
    
}
int16_t  get_clr (vector<string> seq, int i) {      //gets the colornum--as in fx123
if ((seq.at(i)[1])=='1') return RED;
else if (seq.at(i)[1]=='2') return IR;
else  {
    cout <<"unknown color: "<< seq.at(i) << endl;
    return -1;
        }
    
}

 

void defSeq(void){
    
// SeqEntry seqList[NumSeqs];

// seqList[seq].seqnum = seq;
// seqList[seq].seqcomment ="hello";
int seq = 0;
seqList[seq].seqnum = seq;
seqList[seq].seqname = "Face 1(facial two)";
seqList[seq].seqdetail = "f1292,m1100,t120,b13,t120,b13,t120,b13,t120,b13,t114,b11,t17,b13,t121,b13,t119,b13,"  
"t13,b11,t116,b13,t120,b13,t117,b11,t12,b13,t121,b13,t13,f2292,t260,f1292,m1100,t16,b11,t143,b13,t122,b13,t111,b11,t16,b13,t120,b13,t120,b13,t15,b11,t115,"
"b13,t120,b13,t118,b11,t124,b13,t12,f2292,t260,f1292,m1100,t128,b13,t120,b13,t110,b13,t124,b11,t15,b13,t120,b13,t120,b13,t15,b11,t115,b13,t120,b13,t119,"
"b11,t11,b13,t120,b13,f2292,t260,f1292,m1100,t129,b13,t11,b11,t118,b13,t120,b13,t115,b11,t15,b13,t110,b13,t120,b13,t15,b11,t114,b13,t120,b13,t120,b13,"
"t120,b13,f2292,t260,";
seqList[seq].seqcomment = "This is sequence zero--used to be Face 1 button";

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

numbersequences = seq;
 




}

