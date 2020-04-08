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

#include <iostream>
#include <vector>
#include <sstream>
#include <Ticker.h>
#include <cstring>
#include<string>

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

using namespace std;

// #include<string>

#define NumSeqs 20      //max number of sequences

void defSeq(void);
int parse_exec_seq(int step_no, int seq_step );   //returns new seq_step
void out_p_ret(void);
void init_default_profile();

int16_t  get_num (vector<string> seq, int i);  //
int16_t  get_clr (vector<string> seq, int i);

// uint16_t numbersequences;     // calculated

enum colors{RED= 0, IR=1};  //because [] starts at zero.



struct Stage_Spec
{
    uint16_t step_secs;         //time for profile step; up to 32K secs
    uint8_t step_power;         //power 0-255
                                //default 255
    uint16_t step_freq;          //freq 0-10000
                                //default 292
    // colors step_color;          //RED or IR                      
    unsigned int blink_rate;    //blink rate blinks per sec
                                //default 4 (4/sec); max = MAXBLINKTIME
    unsigned int blink_ms;      //milliseconds for blink to be ON
                                //default 100 (100 ms)
    //unsigned int blink_pwr;   //same as power; default 255
    unsigned int bsecs;         //seconds to be blinking
    // unsigned int prescale;      //prescale for ith freq
    // enum profile_states pstate;  //pstate values
//p_idle--not running anything; f_start--start Vis/IR; b_start--start blink Vis/IR
//f_run, b_run-- f is running or blink is underway;                 // 0 = not active, 1 = ready to run, 2=running
};


struct SeqEntry {
  int seqnum;     
  std::string seqname; //human name--i.e Relaxation
  std::string seqdetail; //the sequence
  std::string seqcomment;  //any comment
  };

struct Parse_Return{
  uint out_time;
  uint out_freq;   //frequency for output
  int out_color;  //RED or IR
  bool is_blink;  //True is blink.
};

#endif	/* SEQUENCES_H */


