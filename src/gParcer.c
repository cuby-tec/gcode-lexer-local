
#line 1 "/home/walery/workspace_cdt/Strlen/src/gParcer.rl"
/*
 * A mini G_Code language scanner.
 */


#include "gParcer.h"
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//#include <string.h>
//#include <stddef.h>


//#define BUFLEN 512

typedef void (*gfunction)(size_t, char *, size_t );  // Declare typedef

#define INPUT_BUFSIZE 1024

#define FLOG



enum prsCmd{
	eCommand, eComment, eGcommand, eXparam, eYparam, eZparam, eAparam
	, eBparam, eCparam, eDparam, eEparam, eFparam, eIparam, eJparam
	, eKparam, eLparam, eMparam, eNparam, ePparam, eRparam, eSparam
	, eTpaam, eUparam, eVparam, eWparam, eStarparam,ePunct
	
};


typedef void (*WriteFunc)( char *data, int len );

struct format
{
	char* buf;	//char buf[BUFLEN+1];
	int buflen;
	WriteFunc write;

	int flags;
	int width;
	int prec;
	int cs;
	//--------
	int act;
	char* te;
	char* ts;
	char* p;
	char* pe;
	char* eof;
	int done;	// Исполнение текущего тега.
	int have;
	int curline;
	int space;
	int eofile;
	int lenfile;
	uint state;
};

//#define curline	fsm->curline

//------------------- vars

static const int format_start = 11;
static const int format_first_final = 11;
static const int format_error = 0;

char buf[INPUT_BUFSIZE];


//	int have = 0, curline = 1;
//	char *ts, *te = 0;
//	int done = 0;


	FILE *fp;
	FILE *flog;
//static void (* parser_out)(size_t number, char * param, size_t len);

static gfunction parser_out;

 void command (size_t curline, char * param, size_t len);
 void gcomment (size_t curline, char * param, size_t len);
 void g_command (size_t curline, char * param, size_t len);
 void x_coordinate(size_t curline, char * param, size_t len);
 void y_coordinate(size_t curline, char * param, size_t len);
 void z_coordinate(size_t curline, char * param, size_t len);
 void a_parameter(size_t curline, char * param, size_t len);
 void b_parameter(size_t curline, char * param, size_t len);
 void c_parameter(size_t curline, char * param, size_t len);
 void d_parameter(size_t curline, char * param, size_t len);
 void e_parameter(size_t curline, char * param, size_t len);
 void f_parameter(size_t curline, char * param, size_t len);
 void i_parameter(size_t curline, char * param, size_t len);
 void j_parameter(size_t curline, char * param, size_t len);
 void k_parameter(size_t curline, char * param, size_t len);
 void l_parameter(size_t curline, char * param, size_t len);
 void m_parameter(size_t curline, char * param, size_t len);
 void n_parameter(size_t curline, char * param, size_t len);
 void p_parameter(size_t curline, char * param, size_t len);
 void r_parameter(size_t curline, char * param, size_t len);
 void s_parameter(size_t curline, char * param, size_t len);
 void t_parameter(size_t curline, char * param, size_t len);
 void u_parameter(size_t curline, char * param, size_t len);
 void v_parameter(size_t curline, char * param, size_t len);
 void w_parameter(size_t curline, char * param, size_t len);
 void star_parameter(size_t curline, char * param, size_t len);
 //fprintf(flog, "symbol(%i): %c\n", fsm->curline, fsm->ts[0] );
 void gpunct(size_t curline, char * param, size_t len);

gfunction prs[] = {&command,&gcomment,&g_command,&x_coordinate
	, &y_coordinate	,&z_coordinate,&a_parameter, &b_parameter
	, &c_parameter, &d_parameter, &e_parameter, &f_parameter
	, &i_parameter, &j_parameter, &k_parameter, &l_parameter
	, &m_parameter, &n_parameter, &p_parameter, &r_parameter
	, &s_parameter, &t_parameter, &u_parameter, &v_parameter
	, &w_parameter, &star_parameter, &gpunct };


// g Command
 void command (size_t curline, char * param, size_t len){
#ifdef FLOG
		fprintf(flog, "Command(%lu): ", curline );
		fwrite( param, 1, len, flog );  
		fprintf(flog,"\n");
#endif
#ifdef SCANNER
		b_command(curline,param,len);
#endif
}

 char gBuffer[100];
 
 size_t buffer_index = 0;

 void append(char ch)
 {
 	gBuffer[buffer_index++] = ch;
 }




// g comment
 void gcomment (size_t curline, char * param, size_t len){
#ifdef FLOG
		fprintf(flog, "gcomment(%lu): ", curline );
		fwrite( param, 1, len, flog );  
		fprintf(flog,"\n");
#endif
#ifdef SCANNER		
		b_gcomment(curline,param,len);
#endif
}

// g GXX.X digit 		=command=	command GXX.X
 void g_command (size_t curline, char * param, size_t len){
#ifdef FLOG	 
		fprintf(flog, "G command(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n");
#endif
#ifdef SCANNER		
		b_g_command (curline, param, len);
#endif
}

// g X coordinate
 void x_coordinate(size_t curline, char * param, size_t len)
{
#ifdef FLOG
	 fprintf(flog, "\tX parameter(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n");
#endif
#ifdef SCANNER		
		b_x_coordinate (curline, param, len);
#endif
}

// g Y 	coordinat
 void y_coordinate(size_t curline, char * param, size_t len)
{
#ifdef FLOG
		fprintf(flog, "\tY parameter(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n");
#endif
#ifdef SCANNER
		b_y_coordinate (curline, param, len);
#endif
}

// g Z 	coordiane Line78
 void z_coordinate(size_t curline, char * param, size_t len)
{
#ifdef FLOG
		fprintf(flog, "\tZ parameter(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n");
#endif
#ifdef SCANNER
		b_z_coordinate (curline, param, len);
#endif
}

// g A	 decimal   Stepper A position or angle {Annn] 

 void a_parameter(size_t curline, char * param, size_t len)
{
#ifdef FLOG
	 fprintf(flog, "\tA parameter(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n");
#endif
#ifdef SCANNER
		b_a_parameter (curline, param, len);
#endif
}

// g B	 decimal Stepper B position or angle {Bnnn}
 void b_parameter(size_t curline, char * param, size_t len)
{
#ifdef FLOG
		fprintf(flog, "\tB parameter(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n");
#endif
#ifdef SCANNER
		b_b_parameter (curline, param, len);
#endif
}

// g C	 decimal Stepper C position or angle {Cnnn}
 void c_parameter(size_t curline, char * param, size_t len)
{
#ifdef FLOG
		fprintf(flog, "\tC parameter(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n");
#endif
#ifdef SCANNER
		b_c_parameter (curline, param, len);
#endif		
}

// g D	 none Adjust Diagonal Rod {D}
 void d_parameter(size_t curline, char * param, size_t len)
{
#ifdef FLOG
		fprintf(flog, "\tD parameter(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n");
#endif
#ifdef SCANNER
		b_d_parameter (curline, param, len);
#endif		
}

// g E	 optional coordinate
 void e_parameter(size_t curline, char * param, size_t len)
{
#ifdef FLOG
		fprintf(flog, "\tE parameter(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n");
#endif
#ifdef SCANNER
		b_e_parameter (curline, param, len);
#endif		
}

// g F 	decimal Feed rate parameter in G-command
 void f_parameter(size_t curline, char * param, size_t len)
{
#ifdef FLOG
		fprintf(flog, "\tF parameter(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n");
#endif
#ifdef SCANNER
		b_f_parameter (curline, param, len);
#endif		
}

// g I 	optional X offset for arcs and G87 canned cycles
 void i_parameter(size_t curline, char * param, size_t len)
{
#ifdef FLOG
		fprintf(flog, "\tI parameter(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n");
#endif
#ifdef SCANNER
		b_i_parameter (curline, param, len);
#endif		
}

// g J	 decimal Y offset for arcs and G87 canned cycles
 void j_parameter(size_t curline, char * param, size_t len)
{
#ifdef FLOG
		fprintf(flog, "\tJ parameter(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n");
#endif
#ifdef SCANNER
		b_j_parameter (curline, param, len);
#endif
}

// g K 	decimal Z offset for arcs and G87 canned cycles.
 void k_parameter(size_t curline, char * param, size_t len)
{
#ifdef FLOG
		fprintf(flog, "\tK parameter(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n");
#endif
#ifdef SCANNER
		b_k_parameter (curline, param, len);
#endif
}

// g L 			decimal	 generic parameter word for G10, M66 and others
 void l_parameter(size_t curline, char * param, size_t len)
{
#ifdef FLOG
		fprintf(flog, "\tL parameter(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n");
#endif
#ifdef SCANNER
		b_l_parameter (curline, param, len);
#endif		
}

// g M 	digit 	= command= Code Modal Groups
 void m_parameter(size_t curline, char * param, size_t len)
{
#ifdef FLOG
		fprintf(flog, "M command(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n");
#endif
#ifdef SCANNER
		b_m_parameter (curline, param, len);
#endif	
}

// g N digit				Line number
 void n_parameter(size_t curline, char * param, size_t len)
{
#ifdef FLOG
		fprintf(flog, "\tN parameter(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n");
#endif
#ifdef SCANNER
		b_n_parameter (curline, param, len);
#endif		
}

// g P	alnum_u		Command parameter, such as time in milliseconds; proportional (Kp) in PID Tuning 
 void p_parameter(size_t curline, char * param, size_t len)
{
#ifdef FLOG
		fprintf(flog, "\tP parameter(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n");
#endif
#ifdef SCANNER
		b_p_parameter (curline, param, len);
#endif		
}

// g R 	optional	Arc radius or canned cycle plane
 void r_parameter(size_t curline, char * param, size_t len)
{
#ifdef FLOG
		fprintf(flog, "\tR parameter(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n");
#endif
#ifdef SCANNER
		b_r_parameter (curline, param, len);
#endif		
}

// g S	optional	Spindle speed; Command parameter, such as time in seconds; temperatures; voltage to send to a motor 
 void s_parameter(size_t curline, char * param, size_t len)
{
#ifdef FLOG
		fprintf(flog, "\tS parameter(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n");
#endif
#ifdef SCANNER
		b_s_parameter (curline, param, len);
#endif		
}

// g T	digit	=command= 	Tool selection
 void t_parameter(size_t curline, char * param, size_t len)
{
#ifdef FLOG
		fprintf(flog, "\tT parameter(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n");
#endif
#ifdef SCANNER
		b_t_parameter (curline, param, len);
#endif		
}

// g U	optional  	U axis of machine;
 void u_parameter(size_t curline, char * param, size_t len)
{
#ifdef FLOG
		fprintf(flog, "\tU parameter(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n");
#endif
#ifdef SCANNER
		b_u_parameter (curline, param, len);
#endif		
}

// g V	optional  	V axis of machine;
 void v_parameter(size_t curline, char * param, size_t len)
{
#ifdef FLOG
		fprintf(flog, "\tV parameter(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n");
#endif
#ifdef SCANNER
		b_v_parameter (curline, param, len);
#endif		
}

// g W	optional  	W axis of machine;
 void w_parameter(size_t curline, char * param, size_t len)
{
#ifdef FLOG
		fprintf(flog, "\tW parameter(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n");
#endif
#ifdef SCANNER
		b_w_parameter (curline, param, len);
#endif		
}

// g *	digit		Checksum 
 void star_parameter(size_t curline, char * param, size_t len)
{
#ifdef FLOG
		fprintf(flog, "\tchecksum_lit(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n");
#endif
#ifdef SCANNER
		b_star_parameter (curline, param, len);
#endif		
}

void gpunct(size_t curline, char * param, size_t len)
{
#ifdef FLOG
	fprintf(flog, "symbol(%lu): %c\n", curline, *param );
#endif
#ifdef SCANNER
	b_punct(curline, param, len);
#endif	
}




// 		punct			Symbols.


#line 795 "/home/walery/workspace_cdt/Strlen/src/gParcer.rl"



#line 492 "/home/walery/workspace_cdt/Strlen/src/gParcer.c"
static const char _gparcer_actions[] = {
	0, 1, 1, 2, 1, 2, 2, 1, 
	3, 3, 1, 2, 0, 3, 1, 3, 
	0
};

static const char _gparcer_key_offsets[] = {
	0, 0, 2, 3, 4, 6, 7, 8, 
	9
};

static const char _gparcer_trans_keys[] = {
	59, 71, 10, 10, 48, 57, 10, 10, 
	10, 10, 0
};

static const char _gparcer_single_lengths[] = {
	0, 2, 1, 1, 0, 1, 1, 1, 
	1
};

static const char _gparcer_range_lengths[] = {
	0, 0, 0, 0, 1, 0, 0, 0, 
	0
};

static const char _gparcer_index_offsets[] = {
	0, 0, 3, 5, 7, 9, 11, 13, 
	15
};

static const char _gparcer_indicies[] = {
	0, 2, 1, 3, 0, 4, 0, 5, 
	1, 6, 5, 7, 5, 4, 0, 7, 
	5, 0
};

static const char _gparcer_trans_targs[] = {
	2, 0, 4, 3, 7, 5, 6, 8
};

static const char _gparcer_trans_actions[] = {
	1, 0, 1, 3, 9, 1, 6, 13
};

static const int gparcer_start = 1;
static const int gparcer_first_final = 7;
static const int gparcer_error = 0;

static const int gparcer_en_main = 1;


#line 798 "/home/walery/workspace_cdt/Strlen/src/gParcer.rl"


struct format fsm;




int format_finish( struct format *fsmp )
{
	if ( fsmp->cs == format_error )
		return -1;
	if ( fsmp->cs >= format_first_final )
		return 1;
	return 0;
}

void format_init( struct format *fsm )
{
	buffer_index = 0;
	fsm->buflen = 0;
	fsm->done = 0;
	//int cs, act, have = 0, curline = 1;
	fsm->have = 0;
	fsm->curline = 1;
	fsm->state = 0;
	
#line 572 "/home/walery/workspace_cdt/Strlen/src/gParcer.c"
	{
	( fsm->cs) = gparcer_start;
	}

#line 824 "/home/walery/workspace_cdt/Strlen/src/gParcer.rl"
}

void format_execute( struct format *fsm, char *data, int len, int isEof )
{
//	const char *p = data;
//	const char *pe = data + len;
//	const char *eof = isEof ? pe : 0;
	fsm->p = data;
	fsm->pe = data+len;
	fsm->eof = isEof ? fsm->pe : 0;
	printf("format_execute[747]: len:%d  done:%d line:%d \n",len,fsm->done,fsm->curline);
	if(len == 0)
		return;
	
#line 592 "/home/walery/workspace_cdt/Strlen/src/gParcer.c"
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const char *_keys;

	if ( ( fsm->p) == ( fsm->pe) )
		goto _test_eof;
	if ( ( fsm->cs) == 0 )
		goto _out;
_resume:
	_keys = _gparcer_trans_keys + _gparcer_key_offsets[( fsm->cs)];
	_trans = _gparcer_index_offsets[( fsm->cs)];

	_klen = _gparcer_single_lengths[( fsm->cs)];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( (*( fsm->p)) < *_mid )
				_upper = _mid - 1;
			else if ( (*( fsm->p)) > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (unsigned int)(_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _gparcer_range_lengths[( fsm->cs)];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( (*( fsm->p)) < _mid[0] )
				_upper = _mid - 2;
			else if ( (*( fsm->p)) > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += (unsigned int)((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
	_trans = _gparcer_indicies[_trans];
	( fsm->cs) = _gparcer_trans_targs[_trans];

	if ( _gparcer_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _gparcer_actions + _gparcer_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 0:
#line 740 "/home/walery/workspace_cdt/Strlen/src/gParcer.rl"
	{
//		if ( fsm->buflen > 0 )
//			fsm->write( fsm->buf, fsm->buflen );
//		fwrite("End\n",1,4,stdout);
		printf("\n action finish_ok.\n");
	}
	break;
	case 1:
#line 755 "/home/walery/workspace_cdt/Strlen/src/gParcer.rl"
	{
		append((*( fsm->p)));
	}
	break;
	case 2:
#line 762 "/home/walery/workspace_cdt/Strlen/src/gParcer.rl"
	{
		(*prs[eComment])(fsm->curline ,gBuffer,buffer_index);
//		printf("onBuffer: %s", gBuffer);

	}
	break;
	case 3:
#line 776 "/home/walery/workspace_cdt/Strlen/src/gParcer.rl"
	{
		(*prs[eGcommand])(fsm->curline ,gBuffer,buffer_index);
	}
	break;
#line 695 "/home/walery/workspace_cdt/Strlen/src/gParcer.c"
		}
	}

_again:
	if ( ( fsm->cs) == 0 )
		goto _out;
	if ( ++( fsm->p) != ( fsm->pe) )
		goto _resume;
	_test_eof: {}
	_out: {}
	}

#line 838 "/home/walery/workspace_cdt/Strlen/src/gParcer.rl"
	
		if ( format_finish( fsm ) <= 0 )
		printf("[602] FAIL :finish code:%d  %-10s \n", format_finish( fsm ) ,data);

	
}

void init(){
	format_init(&fsm);
}

void execute(char *data, int len){
	fsm.done = 0;
	format_execute(&fsm, data, len, false);
}

int finish(){
	return (format_finish(&fsm));
}

void scanner(){
scannerstart:
	switch (fsm.state)
	{
	case 0:
		fsm.space = INPUT_BUFSIZE - fsm.have;
		fsm.p = fsm.buf + fsm.have;
		
		if ( fsm.space == 0 ) {
			/* We've used up the entire buffer storing an already-parsed token
			 * prefix that must be preserved. */
			fprintf(stderr, "OUT OF BUFFER SPACE\n" );
			exit(1);
		}
	
		fsm.lenfile = fread( fsm.buf+fsm.have, 1, fsm.space, fp );
		
		fsm.eofile = fsm.lenfile != fsm.space;
		
		format_execute( &fsm, fsm.p, fsm.lenfile, fsm.eofile );
		fsm.state = 1;
		 return;
	
	case 1:
		if(fsm.done)
		{
			fsm.done = 0;
			fsm.lenfile = INPUT_BUFSIZE - (fsm.pe - fsm.buf);
			format_execute( &fsm, fsm.pe, fsm.lenfile, fsm.eofile );
			return;
		}
	case 3:
//		printf("[646] done:  %i \n", fsm.done);
		if ( fsm.eofile ){
//			fprintf(stderr, " [650] EOF lenfile:%i  space:%i \n", fsm.lenfile , fsm.space);
			return;
		//	break;
		}	
		
		if ( fsm.ts == 0 ){
			fsm.have = 0;
		}
		else {
			/* There is a prefix to preserve, shift it over. */
			fsm.have = fsm.pe - fsm.ts;
			memmove( fsm.buf, fsm.ts, fsm.have );
			fsm.te = fsm.buf + (fsm.te-fsm.ts);
			fsm.ts = fsm.buf;
		}
	
	}
	
	fsm.state = 0;
	goto scannerstart;

}

#ifndef SCANNER
int _main(int argc, char* argv[])
{

//	int eofile;
//	int len;

	fsm.buf = buf;
	format_init( &fsm );

	char* gfile = "exmple.gcode";
	char* logFile = "gParcer.log";
	
	if(argc == 2){
		gfile = argv[1];
		printf("main[832] param0:%s\n",argv[1]);
	}
	
	if(argc == 3){
		gfile = argv[1];
		logFile = argv[2];
		printf("main[841] gfile:%s\n",gfile);
		printf("main[842] logFile:%s\n",logFile);
	}
	
	
	fp = fopen(gfile,"r");
	   if (fp==NULL) 
	   {
//	   fputs ("File error:"+gfile,stderr); exit (1);
		   fprintf(stderr,"File error: %s",gfile);
	   }else{
		   printf("Open G-file:%s\n",gfile);
	   
	   }
	   
	   
	flog = fopen(logFile,"w");
	   if (flog==NULL) {
//		   fputs ("File error",stderr); exit (1);
		   fprintf(stderr,"Log file error:%s",logFile);
	   }else{
		   printf("Open log file:%s\n",logFile);
	   }


	while(!fsm.eof)
	{	
		scanner();
	}
	
	if ( format_finish( &fsm ) <= 0 )
		printf("[679] FAIL  %li \n", (unsigned long)&fsm);

	printf("main[871]:  %i \n", format_finish( &fsm ));
	
	fclose(fp);
	fclose(flog);
	return 0;
}
#endif
