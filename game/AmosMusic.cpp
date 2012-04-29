#include <iostream>
#include <cstdio>
#include <string>
#include <vector>

#include "AmosMusic.h"
#include <Engine2d/Utils.h>

using namespace std;

unsigned long peek(unsigned char *adr) {
	return adr[0];
}
void poke(unsigned char *adr,unsigned long v) {
	adr[0] = (unsigned char)(v%256);
}
unsigned long deek(unsigned char *adr) {
	return adr[0]*256 + adr[1];
}
void doke(unsigned char *adr,unsigned long v) {
	adr[0] = (unsigned char)((v/256)%256);
	adr[1] = (unsigned char)(v%256);
}
unsigned long leek(unsigned char *adr) {
	return adr[0]*256*256*256 + adr[1]*256*256 + adr[2]*256 + adr[3];
}
void loke(unsigned char *adr,unsigned long v) {
	adr[0] = (unsigned char)((v/(256*256*256))%256);
	adr[1] = (unsigned char)((v/(256*256))%256);
	adr[2] = (unsigned char)((v/256)%256);
	adr[3] = (unsigned char)(v%256);
}
string speek(unsigned char *adr,long len) {
	string s="";
	for( long i=0; i<len && adr[i]!=0; ++i ) {
		s += adr[i];
	}
	return s;
}
void spoke(unsigned char *adr,const string& s, long len) {
	for( long i=0; i<len && s[i]!=0; ++i ) {
		adr[i] = s[i];
	}
}

string hex(long v) {
	char buf[64];
	sprintf(buf,"%lx",v);
	return buf;
}

class Instrument {
public:
	unsigned char *sam_adr;
	int len;
	int rpt_beg, rpt_len;
	int finetune;
	string name;
	Instrument(void) {
		sam_adr = 0;
		len = 0;
		rpt_beg = 0;
		rpt_len = 0;
		finetune = 0;
		name = "";
	}
	~Instrument() {}
};

class InstrList : public vector<Instrument*> {
public:
	~InstrList() {
		InstrList::iterator it;
		for( it=this->begin(); it != this->end(); ++it ) {
			delete (*it);
		}
	}
};

class Song {
public:
	int tempo;
	string name;
	vector<int> play_list;
	Song(void) {
		tempo=0;
		name="";
		play_list.clear();
	}
	~Song() {
	}
};

class Note {
public:
	int sample, period, effect;
	Note(void) {
		clr();
	}
	~Note() {}
	void clr(void) {
		sample=-1;
		period=0;
		effect=-1;
	}
	Note& operator=(const Note& n) {
		sample=n.sample;
		period=n.period;
		effect=n.effect;
		return *this;
	}
};

class Track : public vector<Note> {
};

class Pattern {
public:
	Track track[4];
};

class PattList : public vector<Pattern*> {
public:
	~PattList() {
		PattList::iterator it;
		for( it=this->begin(); it != this->end(); ++it ) {
			delete (*it);
		}
	}
};

void read_track(unsigned char* ta, Pattern *patt,int t) {
//+ I_END=$8000		//koniec sciezki
//+ I_SVOL=$8300
//I_STOP=$8400
//I_REP=$8500
//I_LEDM=$8600
//I_LEDA=$8700
//+ I_TEMPO=$8800
//+ I_INST=$8900
//+ I_ARP=$8A00
//+ I_PORT=$8B00
//+ I_VIB=$8C00
//+ I_VSL=$8D00
//+ I_SLUP=$8E00
//+ I_SLDOWN=$8F00
//+ I_DEL=$9000		//poczekaj kilka ramek (w edytorze byly puste)
//+ I_PJMP=$9100
//
//+ I_PERIOD=$3000

	unsigned long data, code, par;
	bool koniec = false;
	int sam, per, eff, vol;
	Note note;

	sam=-1;
	per=0;
	eff=-1;
	vol=0;
	while(!koniec) {

		data = deek(ta); ta+=2;
		code = data & 0xff00;

		switch( code ) {
			//efekty
			case 0x8A00: //[0]: Arpeggio
				eff = 0x0000 | (data & 0x00ff);
				break;
			case 0x8E00: //[1]: Slide up
				eff = 0x0100 | (data & 0x00ff);
				break;
			case 0x8F00: //[2]: Slide down
				eff = 0x0200 | (data & 0x00ff);
				break;
			case 0x8B00: //[3]: Slide to note
				eff = 0x0300 | (data & 0x00ff);
				break;
			case 0x8C00: //[4]: Vibrato
				eff = 0x0400 | (data & 0x00ff);
				break;
			case 0x8D00: //[10]: Volume slide
				eff = 0x0A00 | (data & 0x00ff);
				break;
			case 0x8800: //[15]: Set speed
				eff = 0x0F00 | ((100/(data & 0x00ff)) & 0x00ff);
				break;

			//inne komendy
			case 0x8000:	//I_END;
				koniec = true;
				break;
			case 0x9100:	//I_PJMP
				eff = 0x0B00 | (data & 0x00ff);
				koniec = true;
				goto i_del;
				break;
			case 0x8900:	//I_INST
				sam = data & 0x00ff;
				eff = -1;
				break;
			case 0x8300:	//I_SVOL
				//ustawiamy tylko gdy jest juz instrukcja "play sample"
				vol = data & 0x00ff;
				eff = 0x0C00 | (data & 0x00ff);
				break;
			case 0x9000:	//I_DEL - delay - koniec jednego bloku instrukcji (wiersza w mod)
				i_del:

				if( per < 57 || per > 1712 )  {
					//poniewaz period moze zawierac parametry do efektow, ktore nie sa obslugiwane przez amosa
					//to probujemy takie sytuacje wykryc (i olac takie efekty)
					per = 0;
				}

				if( sam>=0 && per>0 ) {
					note.sample = sam;
					note.period = per;
				} else {
					note.clr();
				}
				if( eff >=0 ) {
					note.effect = eff;
				} else if( vol>=0 ) {
					note.effect = 0xc00 & (vol&0x3f);	//set volume
				} else {
					note.effect = 0;
				}

				patt->track[t].push_back(note);

				//wstawiamy kilka pustych instrukcji
				par = data & 0x00ff;
				note.clr();
				for( int d=1; d<(int)par; ++d ) {
					patt->track[t].push_back(note);
				}
				per = 0;
				eff = -1;
				break;
			default:
				break;
		}
		if( data & 0x3000 ) {	//set sample period
			per = data & 0xfff;
		}

		if( patt->track[t].size() >= 64 ) koniec = true;
	}

}

void read_patterns(unsigned char* pa, PattList &patt_list) {

	long patt_cnt;
	unsigned char *adr, *at;
	Pattern *patt;

	patt_cnt = deek(pa);
	INFO("Patterns:" + patt_cnt);
	adr = pa+2;
	for( int p=0; p<patt_cnt; ++p ) {
		patt = new Pattern();
		for( int t=0; t<4; ++t ) {
			at = pa+deek(adr);
			read_track(at,patt,t);
			adr+=2;
		}
		patt_list.push_back(patt);
	}


}

void read_instruments(unsigned char *ia, InstrList &inst_list) {
	long inst_cnt;
	long sam_offs, sam_len, rpt_beg, rpt_len, finetune;
	string sam_name;
	Instrument *inst;
	unsigned char *adr;

	inst_cnt = deek(ia);
	INFO("Instruments:" + inst_cnt);
	for( int i=0; i<inst_cnt; ++i ) {
		adr = ia+2+i*32;
		sam_offs = leek(adr);
		sam_len = deek(adr+14) * 2;
		rpt_beg = deek(adr+8);
		rpt_len = deek(adr+10) * 2;
		if( rpt_len > 2 ) rpt_beg *= 4;
		if( rpt_beg > sam_len ) {
			rpt_beg=0;
			rpt_len=0;
		}
		finetune = deek(adr+12);
		sam_name = speek(adr+16,16);

		INFO(string("Sam [") + toString(i) + "] name=" + sam_name + " len=" + hex(sam_len) + " rpt=(" + hex(rpt_beg) + "," + hex(rpt_beg+rpt_len) + ")");
		inst = new Instrument();
		inst->name = sam_name;
		inst->sam_adr = ia+2+sam_offs;
		inst->len = sam_len;
		inst->rpt_beg = rpt_beg;
		inst->rpt_len = rpt_len;
		inst->finetune = finetune;

		inst_list.push_back(inst);
	}
}

void read_song(unsigned char *sa, Song &song) {
	string name;
	int tempo;
	unsigned char *adr;
	long data;

	song.name = speek(sa+18,15);
	INFO("Song name:" + song.name);

	tempo = deek(sa+6);
	song.tempo = tempo;
	INFO(string("Tempo:") + hex(tempo) + " " + toString(tempo));

	INFO("Song list:");
	song.play_list.clear();
	for( adr=sa+34; 0xfffe > (data=deek(adr)); adr+=2 ) {
		song.play_list.push_back(data);
		INFO("  " + data);
	}
}

void write_song(unsigned char *mod,Song &song) {
	//mod name
	spoke(mod,song.name,20);

	unsigned char *adr;
	adr = mod + 20 + 30*31;

	//dlugosc utworu
	poke(adr,song.play_list.size());

	//tempo ???
	poke(adr+1,song.tempo);

	//play list
	for( int s=0; s<(int)(song.play_list.size()); ++s )
		poke(adr+2+s,song.play_list[s]);

	//magic - 31 instruments module
	spoke(adr+130,"M.K.",4);
}

void write_instruments(unsigned char *mod, InstrList &inst_list) {

	unsigned char *adr;
	adr = mod + 20;

	for( int s=0; s<(int)(inst_list.size()); ++s ) {

		//instrument name
		spoke(adr,(inst_list[s])->name,22);

		//length (in words)
		doke(adr+22,(inst_list[s])->len/2);

		//finetune
		doke(adr+24,(inst_list[s])->finetune);

		//repeat start
		doke(adr+26,(inst_list[s])->rpt_beg/2);

		//repeat length
		doke(adr+28,(inst_list[s])->rpt_len/2);

		adr += 30;
	}
}

void write_samples(unsigned char *mod, InstrList &inst_list) {

	int len;
	unsigned char *adr, *sam;
	adr = mod;

	for( int s=0; s<(int)(inst_list.size()); ++s ) {

		len = (inst_list[s])->len;
		sam = (inst_list[s])->sam_adr;

		for( int i=0; i<len; ++i )
			adr[i] = sam[i];

		adr += len;
	}

}

void write_patterns(unsigned char* mod, PattList &patt_list) {
	Pattern *patt;
	Note note;
	int p,i,t;
	unsigned long data, d;
	for( p=0; p<(int)(patt_list.size()); ++p ) {
		patt = patt_list[p];
		for( i=0; i<64; ++i ) {
			for( t=0; t<4; ++t ) {
				if( (int)(patt->track[t].size()) > i ) {
					note = patt->track[t][i];
				} else {
					note.clr();
				}
				data = 0;
				if( note.sample>=0 ) {
					d = note.sample +  1;
					data |= (d & 0x0100) << 24;
					data |= (d & 0x00ff) << 12;
				}
				if( note.effect>=0 ) {
					d = note.effect;
					data |= (d & 0x0fff);
				}
				if( note.period>=0 ) {
					d = note.period;
					data |= (d & 0x0fff) << 16;
				}
				loke(mod,data);
				mod += 4;
			}
		}
	}
}


unsigned char* convert_abk2mod(unsigned char *abk,long len,long &mod_len) {
	unsigned long inst_offs, song_offs, patt_offs;
	long out_len, sam_offs, mod_patt_offs;
	Song song;
	InstrList inst_list;
	PattList patt_list;
	unsigned char* output;

	//---header---
	song_offs = leek(abk+24) + 20;
	patt_offs = leek(abk+28) + 20;
	inst_offs = 36;

	//---data---
	read_song(abk+song_offs,song);
	read_patterns(abk+patt_offs,patt_list);
	read_instruments(abk+inst_offs,inst_list);

	//---calc output len---
	out_len = 20		//nazwa utworu
					+ 30*31	//opis instrumentow
					+ 1			//dlugosc songu
					+ 1			//tempo ???
					+ 128		//play list
					+ 4			//M.K.
					;
	mod_patt_offs = out_len;
	out_len += 1024 * patt_list.size();	//patterny
	sam_offs = out_len;
	for( int i=0; i<(int)(inst_list.size()); ++i ) {
		out_len += (inst_list[i])->len;
	}
	INFO("Output len=" + out_len);

	//---create output---
	output=new unsigned char[out_len];
	for( int i=0; i<out_len; ++i ) {
		output[i]=0;
	}

	write_song(output,song);
	write_patterns(output+mod_patt_offs,patt_list);
	write_instruments(output,inst_list);
	write_samples(output+sam_offs,inst_list);

	mod_len = out_len;
	return output;
}

Mix_Chunk* convert_sam2mixchunk(unsigned char *sam_buf,long sam_len,int freq) {

	int sys_freq, sys_channels;
	Uint16 sys_format;
	SDL_AudioCVT  wav_cvt;
	//Uint32 wav_len;
	Uint8 *raw_buf;
	int ret;

	Mix_QuerySpec(&sys_freq,&sys_format,&sys_channels);

	/* Build AudioCVT */
	ret = SDL_BuildAudioCVT(&wav_cvt,
													AUDIO_S8, 1, freq,
													sys_format, sys_channels, sys_freq);

	/* Check that the convert was built */
	if(ret==-1){
		ERROR("Can not build sample converter");
		return 0;
	}

	/* Setup for conversion */
	wav_cvt.buf=new Uint8[sam_len*wav_cvt.len_mult];
	wav_cvt.len=sam_len;
	memcpy(wav_cvt.buf, sam_buf, sam_len);

	/* And now we're ready to convert */
	SDL_ConvertAudio(&wav_cvt);

	//robimy kopie skonwertowanych danych w taki sam sposob jak to robi MIX (aby MIX mogl to potem zwolnic)
	raw_buf = (Uint8 *)malloc(wav_cvt.len * wav_cvt.len_mult);
	memcpy(raw_buf, wav_cvt.buf, wav_cvt.len * wav_cvt.len_mult);

	Mix_Chunk *raw_chunk;
//	raw_chunk=Mix_QuickLoad_RAW(wav_cvt.buf,wav_cvt.len_cvt);
	raw_chunk=Mix_QuickLoad_RAW(raw_buf,wav_cvt.len_cvt);
	if( 0 == raw_chunk ) {
		ERROR("Error converting sample: " + Mix_GetError());
		delete[] wav_cvt.buf;
		free(raw_buf);
		return 0;
	}

	delete[] wav_cvt.buf;

	//free(raw_buf); //raw_buf nie zwalniamy, bo Mix_QuickLoad_RAW nie robi sobie kopi danych, tylko jezdzi po przekazanym buforze
	//za to zmusimy biblioteke MIX do zwolnienia tego bufora przy wywolaniu Mix_FreeChunk
	raw_chunk->allocated = 1;

	return raw_chunk;
}
