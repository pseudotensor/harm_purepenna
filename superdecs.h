// superdefs.h : large data structures not needed by liaison code


/*

to add a new variable:

0) global.h: setup macro to turn on/off memory (a_name) below.

1) Add a variable called a_name that is the *definition* of the memory space

2) Lower down in this file, define a pointer of the same type

3) set_arrays.c: add pointer shifting

4) set_arrays.c: down lower, assign to 0 or valueinit

5) set_array.c: use global.h macro to avoid assignments to memory is turned off

6) Use it!

*/



// below is always used -- never use as temp
extern FTYPE a_p[N1M][N2M][N3M][NPR];	/* space for primitive vars */
// below is always used -- never use as temp
extern FTYPE a_panalytic[N1M][N2M][N3M][NPR];       /* space for primitive vars */

// below is always used -- never use as temp
#if(NUMPOTHER>0)
extern FTYPE a_pother[NUMPOTHER][N1M][N2M][N3M];	/* space for primitive vars */
#endif

// arbitrary temporary storage array
extern FTYPE a_ptemparray[N1M][N2M][N3M][NPR];


// emf has extra zone on upper end since corner quantity and some components exist that are needed for cell centered quantities
extern FTYPE a_emf[NDIM][N1M+SHIFT1][N2M+SHIFT2][N3M+SHIFT3];	/* space for emf */

#if(STOREFLUXSTATE)
extern struct of_state a_fluxstate[COMPDIM][NUMLEFTRIGHT][N1M][N2M][N3M];
#endif

#if(FIELDTOTHMEM)
// emf and vconemf assumed not used across substeps so can use as temp var
// below was [COMPDIM] but wanted to use emf as simple temp space for 4D
extern FTYPE a_vconemf[N1M][N2M][N3M][NDIM-1];	/* used for Athena EMFs */
#endif

#if(TRACKVPOT)
extern FTYPE a_vpotarray[NDIM][N1M+SHIFT1][N2M+SHIFT2][N3M+SHIFT3];
#endif



#if(STOREWAVESPEEDS)
// below is used within substeps but not across
extern FTYPE a_wspeedtemp[N1M][N2M][N3M][NUMCS]; // temporarily store wspeed in case not just copying but averaging before putting into wspeed array
extern FTYPE a_wspeed[COMPDIM][NUMCS][N1M][N2M][N3M]; // wave speeds (left/right)
#endif




////////////////////////////////////////////////
//
// TIME-STEPPING
//
////////////////////////////////////////////////

// below is used within substeps AND across substeps but not across full timesteps
extern FTYPE a_pk[MAXDTSTAGES][N1M][N2M][N3M][NPR];	/* next-step primitives */
// for higher order RK time stepping integrations
extern FTYPE a_unew[N1M][N2M][N3M][NPR]; // used across substeps and across full time steps
extern FTYPE a_ulast[N1M][N2M][N3M][NPR]; // used across substeps but not across full time steps
extern FTYPE a_uinitial[N1M][N2M][N3M][NPR]; // used across substeps but not across full time steps
extern FTYPE a_dUgeomarray[N1M][N2M][N3M][NPR]; // assume not used across substeps so can use as temp var

#if(HIGHERORDERMEM||FIELDSTAGMEM)
// below is used within substeps but not across
extern FTYPE a_upoint[N1M][N2M][N3M][NPR];
#endif




////////////////////////////////////////////////
//
// SPATIAL INTERPOLATION
//
////////////////////////////////////////////////


#if(N1>1)
// below is used within substeps but not across if doing ACCURATEDIAG
extern FTYPE a_F1[N1M][N2M][N3M][NPR];	/* fluxes */
#endif
#if(N2>1)
// below is used within substeps but not across if doing ACCURATEDIAG
extern FTYPE a_F2[N1M][N2M][N3M][NPR];	/* fluxes */
#endif
#if(N3>1)
// below is used within substeps but not across if doing ACCURATEDIAG
extern FTYPE a_F3[N1M][N2M][N3M][NPR];	/* fluxes */
#endif

#if(SPLITMAEMMEM)
#if(N1>1)
// below is used within substeps but not across if doing ACCURATEDIAG
extern FTYPE a_F1EM[N1M][N2M][N3M][NPR];	/* fluxes */
#endif
#if(N2>1)
// below is used within substeps but not across if doing ACCURATEDIAG
extern FTYPE a_F2EM[N1M][N2M][N3M][NPR];	/* fluxes */
#endif
#if(N3>1)
// below is used within substeps but not across if doing ACCURATEDIAG
extern FTYPE a_F3EM[N1M][N2M][N3M][NPR];	/* fluxes */
#endif
#endif


#if(SPLITNPR||FIELDSTAGMEM)
// below 2 assume not used across substeps so can use as temp var
extern FTYPE a_gp_l[NDIM-1][N1M][N2M][N3M][NPR2INTERP];
extern FTYPE a_gp_r[NDIM-1][N1M][N2M][N3M][NPR2INTERP];
#endif

extern FTYPE a_pleft[N1M][N2M][N3M][NPR2INTERP]; /* for parabolic interpolation */
extern FTYPE a_pright[N1M][N2M][N3M][NPR2INTERP]; /* for parabolic interpolation */
// below is used within substeps but not across
extern FTYPE a_prc[N1M][N2M][N3M][NPR2INTERP];	/* rescaled primitives, also used for temporary storage in fixup_utoprim() */



#if(FIELDSTAGMEM)
// use unew,ulast,uinitial to store conserved staggered field even for non-finite-volume methods since always available
// need to set unew/uinitial with staggered field initially at t=0
// note fixup mods to unew when doing finite volume never change field, so no conflict with staggered use
// at some point pleft/pright to staggered B field from u(new/last/initial?) so pleft/pright well-defined
// at some point need to fill p[] with interpolated version of staggered field so p[] well-defined
// pleftcorn/prightcorn are interpolated from pleft/pright
// ensure STOREWAVESPEEDS is on
// assume need not store separate wavespeed for corn, just use stored wspeed when needed during specific flux calculation (no interpolation)
//FTYPE a_wspeedcorn[COMPDIM][NUMCS][N1M][N2M][N3M]; // wave speeds (left/right) at corner (not true corner)
extern FTYPE a_pstagscratch[N1M][N2M][N3M][NPR]; // for interpolate_pfield_face2cent() -- only contains fields
// below has more memory than needed for 2nd COMPDIM (can be 2) but leave as 3 for simplicity in accessing array
extern FTYPE a_pbcorninterp[COMPDIM][COMPDIM][NUMCS][N1M+SHIFT1][N2M+SHIFT2][N3M+SHIFT3]; // holds field corner interpolations
extern FTYPE a_pvcorninterp[COMPDIM][COMPDIM][NUMCS][NUMCS][N1M+SHIFT1][N2M+SHIFT2][N3M+SHIFT3]; // holds velocity corner interpolations

#if(HIGHERORDERMEM)
// below used to store Bhat that satisfies divBhat=0 for fluxrecon method when evolving point field at higher order since then unew doesn't contain Bhat
extern FTYPE a_Bhat[N1M][N2M][N3M][NPR];
#endif

// below is used to store de-averaged field in each direction for UNSPLIT scheme or 2D
// used in general, but only different if FV method
// first 3 are directions orthogonal to field given by B1,B2,B3 in NDIM
//FTYPE a_pb1davg[3][N1M][N2M][N3M][3];

#endif



////////////////////////////////////////////////
//
// OLD SPATIAL INTERPOLATION
//
////////////////////////////////////////////////


#if(DODQMEMORY)
#if(N1>1)
// below is used within substeps but not across
extern FTYPE a_dq1[N1M][N2M][N3M][NPR2INTERP];	/* slopes */
#endif
#if(N2>1)
// below is used within substeps but not across
extern FTYPE a_dq2[N1M][N2M][N3M][NPR2INTERP];	/* slopes */
#endif
#if(N3>1)
// below is used within substeps but not across
extern FTYPE a_dq3[N1M][N2M][N3M][NPR2INTERP];	/* slopes */
#endif
#endif



////////////////////////////////////////////////
//
// HIGHER ORDER STUFF
//
////////////////////////////////////////////////

#if(HIGHERORDERMEM)

// termporary storage for flux
extern FTYPE a_fluxvectemp[N1M][N2M][N3M][NPR];

extern FTYPE a_Fa[N1M][N2M][N3M][NPR];	/* fluxes */
extern FTYPE a_Fb[N1M][N2M][N3M][NPR];	/* fluxes */

extern FTYPE a_stencilvartemp[N1M][N2M][N3M][NPR];

#endif












///////////////////////////
//
// COUNTERS and failure checks
//
////////////////////////////



#if( WENO_REDUCE_A2C_LOOK_OTHER_DIRECTIONS )
extern FTYPE a_weno_lower_order_fraction[N1M][N2M][N3M][NPR];	/* space for lower order indicators */  //atch
extern FTYPE do_weno_lower_order_fraction;
#endif 

#if( STORE_GAMMA_PRIM_REDUCTION_FRACTION )
extern FTYPE a_weno_prim_lower_order_fraction[NDIM][N1M][N2M][N3M];	/* space for lower order fraction of primitive quantities */  //atch
#endif 


////////////////////////////////////////////////
//
// DEBUG STUFF USUALLY OFF
//
////////////////////////////////////////////////

#if(DOENODEBUG)
// 3: 1,2,3 directions
// 5: c2e on P, a2c on U, c2a for U, c2a for Fperp1, c2a for Fperp2
extern CTYPE a_enodebugarray[N1M][N2M][N3M][3-1][NUMINTERPTYPES][NPR-4][NUMENODEBUGS];// space for debugging eno
#endif

#if(FLUXDUMP)
extern FTYPE a_fluxdump[N1M][N2M][N3M][NUMFLUXDUMP];
#endif


////////////////////////////////////////////////
//
// DEBUG STUFF USUALLY ON
//
////////////////////////////////////////////////

extern PFTYPE a_pflag[N1M][N2M][N3M][NUMPFLAGS];	/* space for flag */

/* for debug */
#if(DODEBUG)
extern CTYPE a_failfloorcount[N1M][N2M][N3M][NUMTSCALES][NUMFAILFLOORFLAGS]; // number of failures and floor adjustments for each zone
#endif


////////////////////////////////////////////////
//
// other diagnostics
//
////////////////////////////////////////////////


#if(DODISS)
extern FTYPE a_dissfunpos[N1M][N2M][N3M][NUMDISSFUNPOS]; // storage for dissipation function
#endif

#if(CALCFARADAYANDCURRENTS)
// current density stuff
// below 3 are used within and across substeps and full steps (for diagnostics)
extern FTYPE a_cfaraday[N1M][N2M][N3M][NUMCURRENTSLOTS][3];
extern FTYPE a_fcon[N1M][N2M][N3M][NUMFARADAY];
extern FTYPE a_jcon[N1M][N2M][N3M][NDIM];
#endif


////////////////////////////////////////////////
//
// AVG diagnostics
//
////////////////////////////////////////////////
#if(DOAVG)
// time average stuff
extern FTYPE a_normalvarstavg[N1M][N2M][N3M][NUMNORMDUMP];
extern FTYPE a_anormalvarstavg[N1M][N2M][N3M][NUMNORMDUMP];

#if(CALCFARADAYANDCURRENTS)
extern FTYPE a_jcontavg[N1M][N2M][N3M][NDIM];
extern FTYPE a_jcovtavg[N1M][N2M][N3M][NDIM];
extern FTYPE a_ajcontavg[N1M][N2M][N3M][NDIM];
extern FTYPE a_ajcovtavg[N1M][N2M][N3M][NDIM];
#endif

extern FTYPE a_massfluxtavg[N1M][N2M][N3M][NDIM];
extern FTYPE a_amassfluxtavg[N1M][N2M][N3M][NDIM];

extern FTYPE a_othertavg[N1M][N2M][N3M][NUMOTHER];
extern FTYPE a_aothertavg[N1M][N2M][N3M][NUMOTHER];

#if(CALCFARADAYANDCURRENTS)
extern FTYPE a_fcontavg[N1M][N2M][N3M][NUMFARADAY];
extern FTYPE a_fcovtavg[N1M][N2M][N3M][NUMFARADAY];
extern FTYPE a_afcontavg[N1M][N2M][N3M][NUMFARADAY];
extern FTYPE a_afcovtavg[N1M][N2M][N3M][NUMFARADAY];
#endif

extern FTYPE a_tudtavg[N1M][N2M][N3M][NUMSTRESSTERMS];
extern FTYPE a_atudtavg[N1M][N2M][N3M][NUMSTRESSTERMS];
#endif


#if(DOAVG2D)
// *2D* time average stuff: only one element in X3
extern FTYPE a_vars2dtavg[NUM2DAVGDUMP][N1M][N2M][1];
#endif


#if(DODUMP2D)
// *2D* time average stuff: only one element in X3
extern FTYPE a_vars2ddump[NUM2DDUMP][N1M][N2M][1];
#endif

#if(DODUMP2DDUFLOOR)
// *2D* time average stuff: only one element in X3
extern FTYPE a_vars2ddufloor[NUM2DDUFLOOR][N1M][N2M][1];
#endif



///////////////////////////////
//
// grid functions (+1 size larger so can have geometry at upper corners -- say for vector potential or whatever)
//
///////////////////////////////
#if(MCOORD!=CARTMINKMETRIC)

// grid functions that exist at multiple locations within a cell
extern FTYPE a_gcon[N1M+SHIFT1][N2M+SHIFT2][N3M+SHIFT3][NPG][NDIM][NDIM];
extern FTYPE a_gcov[N1M+SHIFT1][N2M+SHIFT2][N3M+SHIFT3][NPG][NDIM][NDIM];
extern FTYPE a_gcovpert[N1M+SHIFT1][N2M+SHIFT2][N3M+SHIFT3][NPG][NDIM];
extern FTYPE a_alphalapse[N1M+SHIFT1][N2M+SHIFT2][N3M+SHIFT3][NPG];
#if(DOEVOLVEMETRIC)
// used to evolve metric in time, so that connection has terms due to dg/dt
extern FTYPE a_gcovlast[N1M+SHIFT1][N2M+SHIFT2][N3M+SHIFT3][NPG][NDIM][NDIM];
extern FTYPE a_gcovpertlast[N1M+SHIFT1][N2M+SHIFT2][N3M+SHIFT3][NPG][NDIM];
extern FTYPE a_alphalapselast[N1M+SHIFT1][N2M+SHIFT2][N3M+SHIFT3][NPG];
#endif

extern FTYPE a_gdet[N1M+SHIFT1][N2M+SHIFT2][N3M+SHIFT3][NPG];

#if(WHICHEOM!=WITHGDET)
extern FTYPE a_eomfunc[N1M+SHIFT1][N2M+SHIFT2][N3M+SHIFT3][NPG];
#endif

#if(GDETVOLDIFF)
extern FTYPE a_gdetvol[N1M+SHIFT1][N2M+SHIFT2][N3M+SHIFT3][NPG]; // for volume regularization of CENT quantities only
#endif

#if(DOSTOREPOSITIONDATA)
extern FTYPE a_dxdxpstore[N1M+SHIFT1][N2M+SHIFT2][N3M+SHIFT3][NPG][NDIM][NDIM];
extern FTYPE a_idxdxpstore[N1M+SHIFT1][N2M+SHIFT2][N3M+SHIFT3][NPG][NDIM][NDIM];
extern FTYPE a_Xstore[N1M+SHIFT1][N2M+SHIFT2][N3M+SHIFT3][NPG][NDIM];
extern FTYPE a_Vstore[N1M+SHIFT1][N2M+SHIFT2][N3M+SHIFT3][NPG][NDIM];
#endif

// rest of grid functions always at center
extern FTYPE a_conn[N1M][N2M][N3M][NDIM][NDIM][NDIM];
extern FTYPE a_conn2[N1M][N2M][N3M][NDIM];
#if(VOLUMEDIFF)
extern FTYPE a_idxvol[N1M][N2M][N3M][NDIM]; // volume regularization 1/dx for each direction
#endif


#else

// grid functions that exist at multiple locations within a cell
extern FTYPE a_gcon[1][1][1][NPG][NDIM][NDIM];
extern FTYPE a_gcov[1][1][1][NPG][NDIM][NDIM];
extern FTYPE a_gcovpert[1][1][1][NPG][NDIM];
extern FTYPE a_alphalapse[1][1][1][NPG];
#if(DOEVOLVEMETRIC)
extern FTYPE a_gcovlast[1][1][1][NPG][NDIM][NDIM];
extern FTYPE a_gcovpertlast[1][1][1][NPG][NDIM];
extern FTYPE a_alphalapselast[1][1][1][NPG];
#endif
extern FTYPE a_gdet[1][1][1][NPG];
extern FTYPE a_eomfunc[1][1][1][NPG];
#if(GDETVOLDIFF)
extern FTYPE a_gdetvol[1][1][1][NPG];
#endif

#if(DOSTOREPOSITIONDATA)
extern FTYPE a_dxdxpstore[1][1][1][NPG][NDIM][NDIM];
extern FTYPE a_idxdxpstore[1][1][1][NPG][NDIM][NDIM];
extern FTYPE a_Xstore[1][1][1][NPG][NDIM];
extern FTYPE a_Vstore[1][1][1][NPG][NDIM];
#endif

// rest of grid functions always at center
extern FTYPE a_conn[1][1][1][NDIM][NDIM][NDIM];
extern FTYPE a_conn2[1][1][1][NDIM];

#if(VOLUMEDIFF)
extern FTYPE a_idxvol[1][1][1][NDIM]; // volume regularization 1/dx for each direction
#endif


#endif









