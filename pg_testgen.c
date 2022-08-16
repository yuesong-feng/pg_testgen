#include "postgres.h"
#include "fmgr.h"
#include "funcapi.h"

PG_MODULE_MAGIC;

static inline int32 rand_int_internal(int min, int max){
    return rand() % (max - min + 1) + min;
}

static inline text *rand_text_internal(int size){
    text *t = (text *)palloc(VARHDRSZ + size);
    SET_VARSIZE(t, VARHDRSZ + size);
    int flag = 0;
    char ch;
    char *p = (char *)VARDATA(t);
    for(int i = 0; i < size; ++i){
        flag = rand() % 3;
        switch(flag){
            case 0:
                ch = 'A' + rand() % 26;
                break;
            case 1:
                ch = 'a' + rand() % 26;
                break;
            case 2:
                ch = '0' + rand() % 10;
                break;
        }
        *p = ch;
        p++;
    }
    return t;
}

PG_FUNCTION_INFO_V1(rand_int);
Datum rand_int(PG_FUNCTION_ARGS){
    Assert(fcinfo->nargs == 0 || fcinfo->nargs == 2);
    int32 min = fcinfo->nargs == 2 ? PG_GETARG_INT32(0) : 0;
    int32 max = fcinfo->nargs == 2 ? PG_GETARG_INT32(1) : INT32_MAX;
    PG_RETURN_INT32(rand_int_internal(min, max));
}

PG_FUNCTION_INFO_V1(rand_text);
Datum rand_text(PG_FUNCTION_ARGS){
    Assert(fcinfo->nargs == 0 || fcinfo->nargs == 1 || fcinfo->nargs == 2);
    int32 size = 0;
    if(fcinfo->nargs == 1){
        size = PG_GETARG_INT32(0);
    } else if(fcinfo->nargs == 0){
        size = rand() % 32 + 1;
    } else if(fcinfo->nargs == 2){
        int32 min = PG_GETARG_INT32(0);
        int32 max = PG_GETARG_INT32(1);
        size = rand() % (max - min + 1) + min;
    }

    text *t = rand_text_internal(size);
    PG_RETURN_TEXT_P(t);
}

PG_FUNCTION_INFO_V1(rows_int);
Datum
rows_int(PG_FUNCTION_ARGS)
{
    Assert(fcinfo->nargs == 1 || fcinfo->nargs == 3);
    
    FuncCallContext     *funcctx;
    int32 times = PG_GETARG_INT32(0);

    /* stuff done only on the first call of the function */
    if (SRF_IS_FIRSTCALL())
    {
        MemoryContext   oldcontext;

        /* create a function context for cross-call persistence */
        funcctx = SRF_FIRSTCALL_INIT();

        /* switch to memory context appropriate for multiple function calls */
        oldcontext = MemoryContextSwitchTo(funcctx->multi_call_memory_ctx);

        /* total number of tuples to be returned */
        funcctx->max_calls = times;

        MemoryContextSwitchTo(oldcontext);
    }

    /* stuff done on every call of the function */
    funcctx = SRF_PERCALL_SETUP();

    if (funcctx->call_cntr < funcctx->max_calls)    /* do when there is more left to send */
    {
        int32 min = fcinfo->nargs == 3 ? PG_GETARG_INT32(1) : 0;
        int32 max = fcinfo->nargs == 3 ? PG_GETARG_INT32(2) : INT32_MAX;
        SRF_RETURN_NEXT(funcctx, Int32GetDatum(rand_int_internal(min, max)));
    }
    else    /* do when there is no more left */
    {
        SRF_RETURN_DONE(funcctx);
    }
}

PG_FUNCTION_INFO_V1(rows_text);
Datum
rows_text(PG_FUNCTION_ARGS)
{
    Assert(fcinfo->nargs == 1 || fcinfo->nargs == 2 || fcinfo->nargs == 3);
    
    FuncCallContext     *funcctx;
    int32 times = PG_GETARG_INT32(0);

    /* stuff done only on the first call of the function */
    if (SRF_IS_FIRSTCALL())
    {
        MemoryContext   oldcontext;

        /* create a function context for cross-call persistence */
        funcctx = SRF_FIRSTCALL_INIT();

        /* switch to memory context appropriate for multiple function calls */
        oldcontext = MemoryContextSwitchTo(funcctx->multi_call_memory_ctx);

        /* total number of tuples to be returned */
        funcctx->max_calls = times;

        MemoryContextSwitchTo(oldcontext);
    }

    /* stuff done on every call of the function */
    funcctx = SRF_PERCALL_SETUP();

    int32 size = 0;
    if(fcinfo->nargs == 2){
        size = PG_GETARG_INT32(1);
    } else if(fcinfo->nargs == 1){
        size = rand() % 32 + 1;
    } else if(fcinfo->nargs == 3){
        int32 min = PG_GETARG_INT32(1);
        int32 max = PG_GETARG_INT32(2);
        size = rand() % (max - min + 1) + min;
    }
    
    if (funcctx->call_cntr < funcctx->max_calls)    /* do when there is more left to send */
    {
        text *t = rand_text_internal(size);
        SRF_RETURN_NEXT(funcctx, PointerGetDatum(t));
    }
    else    /* do when there is no more left */
    {
        SRF_RETURN_DONE(funcctx);
    }
}

