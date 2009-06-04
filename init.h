//undefine the grid size parameters if they have already been defined
#ifdef N1 
#undef N1
#endif

#ifdef N2 
#undef N2
#endif

#ifdef N3 
#undef N3
#endif

#define N1 16
#define N2 16
#define N3 16

// atch adjusts
#undef MAXWELL
#undef TRACKVPOT
#undef EVOLVEWITHVPOT
#undef DOGRIDSECTIONING
#undef MERGEDC2EA2CMETHOD
#undef ACCURATESINCOS
#undef REMOTEHOST
#undef WENO_REDUCE_A2C_LOOK_OTHER_DIRECTIONS
#undef WENO_USE_PRIM_REDUCTION
#undef LIMIT_FLUXC2A_PRIM_CHANGE
#undef COMPDIM
#undef SPLITNPR
#undef FIELDSTAGMEM
#undef HIGHERORDERMEM
#undef MAXBND
#undef MCOORD
#undef PRODUCTION
#undef FULLOUTPUT
#undef MAILWHENDONE
#undef EMAILMESSAGE
#undef EMAILADDRESS 
#undef PERFTEST
#undef DOAVG
#undef DOJETDIAG
#undef DOAVG2
#undef DODEBUG
#undef DO_WENO_DEBUG
#undef DOENODEBUG
#undef DODISS
#undef DOEVOLVEMETRIC
#undef EVOLVEMETRICSUBSTEP
#undef LIMITDTWITHSOURCETERM
#undef DOLUMVSR
#undef DODISSVSR
#undef DOSELFGRAVVSR
#undef DOFIELDLINE
#undef ROEAVERAGEDWAVESPEED
#undef ATHENAROE
#undef STOREWAVESPEEDS
#undef USESTOREDSPEEDSFORFLUX
#undef VCHARTYPE
#undef PRECISEINVERSION
#undef WHICHVEL
#undef WHICHEOM
#undef REMOVERESTMASSFROMUU
#undef RELTYPE
#undef EOMTYPE
#undef UTOPRIMTRYAGAIN
#undef WHICHEOS
#undef CHECKONINVERSION
#undef DOENTROPY
#undef WHICHENTROPYEVOLVE
#undef FIXUPAFTERINIT
#undef FIXUPAFTERRESTART
#undef CHECKSOLUTION
#undef GAMMAPERCDIFFMAX
#undef UPERCDIFFMAX
#undef DOEXTRAINTERP
#undef LIMADJUST
#undef HYDROLIMADJUSTONLY
#undef FLUXADJUST
#undef HYDROFLUXADJUSTONLY
#undef STEPOVERNEGU
#undef STEPOVERNEGRHO
#undef STEPOVERNEGRHOU
#undef UTOPRIMADJUST
#undef UTOPRIMFAILRETURNTYPE
#undef SMOOTHSING
#undef COORDSINGFIX
#undef SINGSMALL
#undef VOLUMEDIFF
#undef GDETVOLDIFF
#undef FIXGDETSPC_WHEN_1DRADIAL
#undef MINDT
#undef JONCHECKS
#undef JONCHECKS2
#undef FLOORDIAGS
#undef ANALYTICGCON
#undef ANALYTICCONNECTION
#undef ANALYTICSOURCE
#undef OUTFLOWAVOIDBC
#undef FLUXDIMENSPLIT
#undef A2CDIMENSPLIT
#undef DODQMEMORY
#undef BOUNDFLUXRECON
#undef DOENOFLUXMEMORY
#undef BOUNDARYINTERPADJUST
#undef COMPUTEFRDOT
#undef CALCFARADAYANDCURRENTS
#undef WHICHCURRENTCALC
#undef FARADAYT0
#undef CURRENTST0

#undef EVOLVECHECKS
#undef FIXUPZONES
#undef HLLBOUNDARY
#undef FIXUPFLUX
#undef ZEROOUTFLOWFLUX
#undef ZEROPOLEFLUX
#undef RESCALEINTERP
#undef BDIRCONT
#undef HYPERHLL
#undef HORIZONSUPERFAST
#undef VARTOINTERP

#undef USEAVGPRIMITIVEFORWENOFLAT
#undef USEPRIMITIVEFROMAVGCONSERVED
#undef CONTACTINDICATOR
#undef COMPUTEDRHODP
#undef SUPERFASTDIVREDUCE
#undef MINPREFORDER
#undef SHOCKINDICATOR
#undef WHICHPARA
#undef HOT2COLD


//#define MAXWELL GENMAXWELL
#define MAXWELL PRIMMAXWELL // more stable in highly-magnetized regime


#define TRACKVPOT 0 // not on by default
#define EVOLVEWITHVPOT 0 // not on by default

#define DOGRIDSECTIONING 0 // not on by default

#define MERGEDC2EA2CMETHOD 0

// jon adjusts
#define WENO_REDUCE_A2C_LOOK_OTHER_DIRECTIONS 1
//#define WENO_USE_LIM_PRIM_CORRECTION_FOR_FLUX_LIMITING 1

#define WENO_USE_PRIM_REDUCTION 1

#define LIMIT_FLUXC2A_PRIM_CHANGE 0



#define MCOORD KSCOORDS
#define COMPDIM 3
#define SPLITNPR 0 // TESTING
#define FIELDSTAGMEM 1 // testing
#define HIGHERORDERMEM 1
#define MAXBND 4 // 4 for PARAFLAT, 6 for WENO5BND wo/a2c stuff : 11 for full point-field FLUXRECON method
#define PRODUCTION 1
//#define FULLOUTPUT MAXBND
#define FULLOUTPUT 0

#define MAILWHENDONE 0
#define MAILFROMREMOTE 0
#define REMOTEHOST "relativity.cfa.harvard.edu"
#define EMAILADDRESS "shafee@fas.harvard.edu"
#define EMAILMESSAGE "Done with GRMHD run DEFAULT"
#define PERFTEST 0
#define DOAVG 0
#define DOJETDIAG 1
#define DOAVG2 0
#define DODEBUG 1
#define DO_WENO_DEBUG 0
#define DOENODEBUG 0
#define DOEVOLVEMETRIC 0
#define EVOLVEMETRICSUBSTEP 1 // evolve metric every substep
#define LIMITDTWITHSOURCETERM 0 // not necessary for Rebecca

// these diagnostics do slow performance a bit when doing TIMEORDER<=2
#define DODISS 1
#define DOLUMVSR 1
#define DODISSVSR 1

#define DOSELFGRAVVSR 0
#define DOFIELDLINE 1
#define ROEAVERAGEDWAVESPEED 0
#define ATHENAROE 0

//set this and the following one to unity to use the DONOR interpolated states for computing wavespeeds
#if(1 || SPLITNPR==1 || FIELDSTAGMEM==1) // should also be on if FLUXB==FIELDSTAG
#define STOREWAVESPEEDS 1 // no choice
#else
#define STOREWAVESPEEDS 0 // choice
#endif

#define USESTOREDSPEEDSFORFLUX (STOREWAVESPEEDS) // choice really

#define VCHARTYPE VERYLOCALVCHAR
#define PRECISEINVERSION 1
#define WHICHVEL VELREL4
#define WHICHEOM WITHGDET
#define REMOVERESTMASSFROMUU 0 // perfectly fine for relativistic problems
#define RELTYPE RELEOM
#define EOMTYPE EOMGRMHD
//#define EOMTYPE EOMFFDE
//#define EOMTYPE EOMCOLDGRMHD
#define UTOPRIMTRYAGAIN 0
#define WHICHEOS IDEALGAS

#define CHECKONINVERSION 0 // can slow things down

#if(DODISS || DOLUMVSR || DODISSVSR)
// for diss: testing CHANGINGMARK
#define DOENTROPY DOEVOLVECOMPAREENTROPY
#define WHICHENTROPYEVOLVE EVOLVEFULLENTROPY
#else
// no diss/entropy
#define DOENTROPY DONOENTROPY
#define WHICHENTROPYEVOLVE EVOLVESIMPLEENTROPY
#endif



#define FIXUPAFTERINIT 1
#define FIXUPAFTERRESTART 1

#define CHECKSOLUTION 0 // not necessary (and can cause problems at horizon)

#define GAMMAPERCDIFFMAX 2.0
#define UPERCDIFFMAX 10.0
#define LIMADJUST LIMITERFIXED
#define HYDROLIMADJUSTONLY 0
#define FLUXADJUST FLUXFIXED
#define HYDROFLUXADJUSTONLY 0
#define STEPOVERNEGU NEGDENSITY_NEVERFIXUP
#define STEPOVERNEGRHO NEGDENSITY_NEVERFIXUP
#define STEPOVERNEGRHOU NEGDENSITY_NEVERFIXUP
#define UTOPRIMADJUST UTOPRIMAVG
#define UTOPRIMFAILRETURNTYPE UTOPRIMRETURNADJUSTED
#define SMOOTHSING 0
#define COORDSINGFIX 0
// whether to move polar axis to a bit larger theta
// theta value where singularity is displaced to
//#define SINGSMALL (1E-3)
#define SINGSMALL (1E-14) // must be larger than machine precision to work for outer M_PI boundary!
// Hawley uses 0.06283 (0.02Pi)

#define VOLUMEDIFF 0
#define GDETVOLDIFF 0 // doesn't help much
#define FIXGDETSPC_WHEN_1DRADIAL 1

#define MINDT 1.e-20 
#define JONCHECKS 1    //SASMARK - do I need this?
#define JONCHECKS2 1   //SASMARK - do I need this?
#define FLOORDIAGS 1
#define ANALYTICGCON 0
#define ANALYTICCONNECTION 0  //SASMARK - Don't I need this?
#define ANALYTICSOURCE 0
#define OUTFLOWAVOIDBC 0
#define FLUXDIMENSPLIT PERFECTUNSPLIT
#define A2CDIMENSPLIT PERFECTUNSPLIT
#define DODQMEMORY 1
#define BOUNDFLUXRECON 0 // can set this to 1 if want to bound fluxes instead for FLUXRECON method (may be useful near poles)
#define DOENOFLUXMEMORY 1
#define BOUNDARYINTERPADJUST 0  //should be set to zero always
#define COMPUTEFRDOT 0
#define CALCFARADAYANDCURRENTS 1
#define WHICHCURRENTCALC CURRENTCALC1
#define FARADAYT0 1
#define CURRENTST0 1


#define EVOLVECHECKS 1
#define FIXUPZONES FIXUP1ZONE
#define HLLBOUNDARY 0
#define FIXUPFLUX 0
#define ZEROOUTFLOWFLUX 0
#define ZEROPOLEFLUX 0
#define BDIRCONT 1
#define HYPERHLL 0
#define HORIZONSUPERFAST 0

#define VARTOINTERP PRIMTOINTERP
//#define VARTOINTERP PRIMTOINTERP_RHOU
//#define VARTOINTERP PRIMTOINTERP_VSQ
// #define VARTOINTERP PRIMTOINTERP_3VELREL_GAMMAREL (used in Sasha tests)
#define RESCALEINTERP 0
#define DOEXTRAINTERP 0

#define USEAVGPRIMITIVEFORWENOFLAT 1
#define USEPRIMITIVEFROMAVGCONSERVED 0
#define CONTACTINDICATOR 0
#define COMPUTEDRHODP 1
#define SUPERFASTDIVREDUCE 0
#define MINPREFORDER 3
#define SHOCKINDICATOR 1
#define WHICHPARA PARA4

#undef DO_VORTICITY_IMAGE
#define DO_VORTICITY_IMAGE 0

#define HOT2COLD 0

#define ACCURATESINCOS 1

#undef FLIPGDETAXIS
//#define FLIPGDETAXIS 1
#define FLIPGDETAXIS 0

#undef BOUNDPLPR
#define BOUNDPLPR 0

#undef NOFLUXCTONX1DN
#define NOFLUXCTONX1DN 0

#undef NUMPANALYTICOTHER
#undef DODUMPOTHER

#define NUMPOTHER 0
#define DODUMPOTHER 0

#undef FLUXDUMP
#define FLUXDUMP 0

struct Ccoordparams {
    double timescalefactor;
}  coordparams;
