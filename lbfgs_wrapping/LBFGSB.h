
extern "C"
{
extern void setulb_(int *n,
					int *m,
					double *x,
					double *l,
					double *u,
					int *nbd,
					double *f,
					double *g,
					double *factr,
					double *pgtol,
					double *fdelta,
					double *wa,
					int *iwa,
					char *task,
					int *iprint,
					char *csave,
					int *lsave,
					int *isave,
					double *dsave,
					int tasklength,
					int csavelength);
}

#define LBFGSB(n,m,x,l,u,nbd,f,g,factr,pgtol,fdelta,wa,iwa,task,iprint,csave,lsave,isave,dsave) setulb_(&(n),&(m),(x),(l),(u),(nbd),&(f),(g),&(factr),&(pgtol),&(fdelta),(wa),(iwa),(task),&(iprint),(csave),(lsave),(isave),(dsave),60,60)


