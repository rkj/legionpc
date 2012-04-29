
#include "Samples.h"
#include "Settings.h"
#include "Utils.h"

using namespace std;
using namespace Core;


namespace Sfx {

PSam :: PSam(void) {
	sample=0;
	len=0;
};
PSam :: ~PSam() {
	if( 0 != sample ) {
		Mix_FreeChunk(sample);
	}
}
void PSam :: Set(Mix_Chunk *sam) {
	sample = sam;
	if( 0 != sample ) {
		len = sample->alen;
	} else {
		len = 0;
	}
}
int PSam :: Load(const std::string& name) {
	sample = Mix_LoadWAV(name.c_str());
	if( 0==sample ) {
		len = 0;
		return -1;
	}
	len = sample->alen;
	return 0;
}
int PSam :: GetLength(void) const {
	return len;
}


void LSam :: _reset(void) {
	sam=0;
	offset=0; len=0;
}
void LSam :: _destroy(void) {
}
Mix_Chunk* LSam :: _GetMixChunk(void) const {
	if( 0 != sam )
		return sam->sample;
	else
		return 0;
}
LSam :: LSam(void) {
	_reset();
}
LSam :: LSam(const PSam *p_sam) {
	_reset();
	Set(p_sam);
}
LSam :: LSam(const PSam *p_sam,int p_offset,int p_len) {
	_reset();
	Set(p_sam,p_offset,p_len);
}
LSam :: ~LSam() {
	_destroy();
}
void LSam :: Set(const PSam *p_sam) {
	sam = p_sam;
	offset = 0;
	if( 0 != p_sam )
		len = p_sam->GetLength();
	else
		len = 0;
}
void LSam :: Set(const PSam *p_sam,int p_offset,int p_len) {
	sam = p_sam;
	offset = p_offset;
	if( 0 != p_sam )
		len = p_sam->GetLength();
	else
		len = 0;
}
int LSam :: GetOffset(void) const {
	return offset;
}
int LSam :: GetLength(void) const {
	return len;
}




void SampleManager :: _reset(void) {
	psam.clear();
	lsam.clear();
}
void SampleManager :: _destroy(void) {
	LSam* lt;
	map<string,LSam*>::iterator lit;
	for( lit=lsam.begin(); lit != lsam.end(); ++lit ) {
		lt = lit->second;
		delete lt;
	}

	PSam* pt;
	map<string,PSam*>::iterator pit;
	for( pit=psam.begin(); pit != psam.end(); ++pit ) {
		pt = pit->second;
		delete pt;
	}
}
SampleManager :: SampleManager(void) {
	_reset();
}
SampleManager :: ~SampleManager() {
	_destroy();
}
bool SampleManager :: ExistsPSam(const string& id) {
	return psam.find(id) != psam.end();
}
bool SampleManager :: ExistsLSam(const string& id) {
	return lsam.find(id) != lsam.end();
}
void SampleManager :: AddPSam(const string& id,PSam* t,bool overwrite) {
	if( ExistsPSam(id) ) {
		if( overwrite ) {
			DelPSam(id);	//usuwamy poprzednia teksture
		} else {
			return;				//jest juz i nienadpisujemy, wiec koniec
		}
	}
	psam[id] = t;
	return;
}
void SampleManager :: AddLSam(const string& id,LSam* t,bool overwrite) {
	if( ExistsLSam(id) ) {
		if( overwrite ) {
			DelLSam(id);	//usuwamy poprzednia teksture
		} else {
			return;				//jest juz i nienadpisujemy, wiec koniec
		}
	}
	lsam[id] = t;
	return;
}

PSam* SampleManager :: GetPSam(const string& id) {
	map<string,PSam*>::const_iterator it;
	it = psam.find(id);
	if( it != psam.end() )
		return it->second;
	return 0;
}

LSam* SampleManager :: GetLSam(const string& id) {
	map<string,LSam*>::const_iterator it;
	it = lsam.find(id);
	if( it != lsam.end() )
		return it->second;
	return 0;
}

PSam* SampleManager :: RemPSam(const string& id) {
	PSam* t = 0;
	map<string,PSam*>::iterator it;
	it = psam.find(id);
	if( it != psam.end() ) {
		t = it->second;
		psam.erase(it);
	}
	return t;
}

LSam* SampleManager :: RemLSam(const string& id) {
	LSam* t = 0;
	map<string,LSam*>::iterator it;
	it = lsam.find(id);
	if( it != lsam.end() ) {
		t = it->second;
		lsam.erase(it);
	}
	return t;
}

void SampleManager :: DelPSam(const string& id) {
	PSam* t;
	map<string,PSam*>::iterator it;
	it = psam.find(id);
	if( it != psam.end() ) {
		t = it->second;
		delete t;
		psam.erase(it);
	}
}

void SampleManager :: DelLSam(const string& id) {
	LSam* t;
	map<string,LSam*>::iterator it;
	it = lsam.find(id);
	if( it != lsam.end() ) {
		t = it->second;
		delete t;
		lsam.erase(it);
	}
}

void SampleManager :: DelAll(void) {
	_destroy();
	_reset();
}

int SampleManager :: CountPSam(void) {
	return psam.size();
}

int SampleManager :: CountLSam(void) {
	return lsam.size();
}


int SampleManager :: Load(const string& filename,const string& root) {
	Settings sets;
	int ret = sets.ReadFile(filename);
	if( ret < 0 ) {
		ERROR("Blad wczytywania pliku z opisem sampli: " + sets.ErrorMsg() );
		return -1;
	}
	return Load(sets,root);
}

int SampleManager :: Load(const Settings& sets,const string& root) {
	if( ! sets.isValid() ) {
		ERROR("Obiekt opisuj¹cy sample jest niewa¿ny");
		return -2;
	}

	Settings s, s1;
	int n, li_ret;
	string id, pid, file_name;
	PSam *pt;
	LSam *lt;
	int ioffset, ilen;

	//usuwamy wszystko
	_destroy();
	_reset();

	//ladujemy sample fizyczne
	if( root != "" )
		s = sets.Extract(root + ".Phisical");
	else
		s = sets.Extract(root + "Phisical");
	if( ! s.isValid() ) {
		ERROR("Blad pobierania danych na temat sampli fizycznych: " + s.ErrorMsg() );
		return -3;
	}
	INFO(s.Dump());

	//TODO - dorobic pobieranie ilosci wpisow o samplach
	n = 1;
	s1 = s.Extract("Phisical["+toString(n)+"]");
	while( s1.isValid() ) {
		INFO("sample<" + toString(n) + ">");
		INFO(s1.Dump());

		id = s1.GetValS("Phisical.ID");
		file_name = s1.GetValS("Phisical.FileName");
		INFO("plik: " + id + " : " + file_name);

		pt = new PSam();
		li_ret = pt->Load(file_name);
		if( li_ret < 0 ) {
			delete pt;
			ERROR("Error loading the sample file (filename=" + file_name + ") !" );
			return -4;
		}

		AddPSam(id,pt);
		INFO("Dodano sampel o id=" + id);

		n++;
		s1 = s.Extract("Phisical["+toString(n)+"]");
	}
	INFO("Blad: " + s1.ErrorMsg());

	//ladujemy sample logiczne
	if( root != "" )
		s = sets.Extract(root + ".Logical");
	else
		s = sets.Extract(root + "Logical");
	if( ! s.isValid() ) {
		ERROR("Blad pobierania danych na temat sampli logicznych: " + s.ErrorMsg() );
		return -4;
	}
	INFO(s.Dump());

	//TODO - dorobic pobieranie ilosci wpisow o tekturach
	n = 1;
	s1 = s.Extract("Logical["+toString(n)+"]");
	while( s1.isValid() ) {
		INFO("sampel<" + toString(n) + ">");
		INFO(s1.Dump());

		id = s1.GetValS("Logical.ID");
		pid = s1.GetValS("Logical.PID");
		ioffset = s1.GetValI("Logical.Offset");
		ilen = s1.GetValI("Logical.Length");

		pt = GetPSam(pid);
		if( 0 == pt ) {
			ERROR("Brak sampla fizycznego o ID=\"" + pid + "\". Sampel logiczny o ID=\"" + id + "\" nie mo¿e byæ utworzony !!!");
		} else {
			lt = new LSam();
			lt->Set(pt,ioffset,ilen);
			AddLSam(id,lt);
			INFO("Dodano sampel o id=" + id);
		}

		n++;
		s1 = s.Extract("Logical["+toString(n)+"]");
	}
	INFO("Blad: " + s1.ErrorMsg());


	INFO("Koniec sampli");

	return 1;
}




int PlaySample(const LSam *sam,int loops) {
	return PlaySample(sam,MIX_MAX_VOLUME,loops);
}
int PlaySample(const LSam *sam,int vol,int loops) {
	int chan;
	chan = Mix_PlayChannel(-1,sam->_GetMixChunk(),loops);
	if( chan >= 0 ) {
		Mix_Volume(chan,vol);
	}
	return chan;
}



};		//namespace
