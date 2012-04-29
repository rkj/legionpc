#ifndef D_ALAN_H_D
#define D_ALAN_H_D

#include <map>

namespace Gfx {

class TextureManager;
class LTex;
class AlanChannel;

class AlanControlable {
protected:
	AlanChannel *channel;
public:
	AlanControlable(void) { channel=0; }
	virtual ~AlanControlable(void) {}
	//metody wykorzystywane przez ALANa do komunikacji z obiektem kontrolowanym
	virtual float AlanGetX(void) { return 0.0f; }
	virtual float AlanGetY(void) { return 0.0f; }
	virtual float AlanGetRot(void) { return 0.0f; }
	virtual float AlanGetScaleX(void) { return 1.0f; }
	virtual float AlanGetScaleY(void) { return 1.0f; }
	virtual float AlanGetTimeFactor(float dt) { return 1.0f; }	//generalnie po to aby moc sterowac predkoscia uplywu czasu z poziomu kontrolowanego obiektu (np. efekt zamrazania obiektu)
	virtual void AlanSetPos(float x,float y) {}
	virtual void AlanSetRot(float r) {}
	virtual void AlanSetScale(float sx,float sy) {}
	virtual void AlanSetTex(LTex* tex) {}
	virtual void AlanSetImg(const std::string& img) {}
	//metody, ktore moga byc wykorzystywane prze obiekt kontrolowany do komunikacji z ALANem
	bool AlanGetVarB(const std::string& name);
	int AlanGetVarI(const std::string& name);
	float AlanGetVarF(const std::string& name);
	std::string AlanGetVarS(const std::string& name);
	void AlanSetVar(const std::string& name,bool v);
	void AlanSetVar(const std::string& name,int v);
	void AlanSetVar(const std::string& name,float v);
	void AlanSetVar(const std::string& name,std::string v);
	friend class AlanChannel;
};

class Alan {

protected:

	TextureManager *tex_mgr;
	bool debug;

	typedef std::map<std::string,void*> t_channels;
	typedef t_channels::iterator tit_channels;
	t_channels lmp_channels;

	void* _findChannel(const std::string& name);
	void _precalc_buildins(void);

public:
	Alan(void);
	~Alan();

	int openChannel(const std::string& name,const std::string& src_code);
	int bindObject(const std::string& channel_name,AlanControlable* obj);
	int closeChannel(const std::string& name);
	int stopChannel(const std::string& name);
	int startChannel(const std::string& name);

	int setTextureMgr(const std::string& channel_name, TextureManager* p_tex_mgr);
	int setTextureMgr(TextureManager* tex_mgr);

	int process(const std::string& name,float dt);
	int process(float dt);
	int debug_process(const std::string& name,float dt);
	int debug_process(float dt);
};

}	//namespace Gfx

#endif
