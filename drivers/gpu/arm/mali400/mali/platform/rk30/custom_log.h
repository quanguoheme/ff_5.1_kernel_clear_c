/*  --------------------------------------------------------------------------------------------------------
 *  File:   custom_log.h 
 *
 *  Desc:   ChenZhen ƫ�õ� log ����Ķ���ʵ��. 
 *
 *          -----------------------------------------------------------------------------------
 *          < ϰ�� �� ������ > : 
 *
 *          -----------------------------------------------------------------------------------
 *  Usage:		
 *
 *  Note:
 *
 *  Author: ChenZhen
 *
 *  --------------------------------------------------------------------------------------------------------
 *  Version:
 *          v1.0
 *  --------------------------------------------------------------------------------------------------------
 *  Log:
	----Fri Nov 19 15:20:28 2010            v1.0
 *        
 *  --------------------------------------------------------------------------------------------------------
 */


#ifndef __CUSTOM_LOG_H__
#define __CUSTOM_LOG_H__

#ifdef __cplusplus
extern "C" {
#endif

/* ---------------------------------------------------------------------------------------------------------
 *  Include Files
 * ---------------------------------------------------------------------------------------------------------
 */
#include <linux/kernel.h>


/* ---------------------------------------------------------------------------------------------------------
 *  Macros Definition 
 * ---------------------------------------------------------------------------------------------------------
 */
    
/** ������ macro �б�����, �� ʹ�� log ���. */
#define ENABLE_DEBUG_LOG

/** .! : ����Ҫȫ�ֵعر� D log, ����ʹ������Ĵ���. */
/*
#undef ENABLE_DEBUG_LOG
#warning "custom debug log is disabled globally!"
*/

#define LOGD(fmt, args...) \
    printk(KERN_DEBUG fmt "\n", ## args)

/*---------------------------------------------------------------------------*/
    
#ifdef ENABLE_VERBOSE_LOG
/** Verbose log. */
#define V(fmt, args...) \
    { printk(KERN_DEBUG "V : [File] : %s; [Line] : %d; [Func] : %s(); " fmt "\n", __FILE__, __LINE__, __FUNCTION__, ## args); }
#else
#define  V(...)  ((void)0)
#endif


#ifdef ENABLE_DEBUG_LOG
/** Debug log. */
#define D(fmt, args...) \
    { printk(KERN_DEBUG "D : [File] : %s; [Line] : %d; [Func] : %s(); " fmt "\n", __FILE__, __LINE__, __FUNCTION__, ## args); }
#else
#define  D(...)  ((void)0)
#endif

#define I(fmt, args...) \
    { printk(KERN_INFO "I : [File] : %s; [Line] : %d; [Func] : %s(); " fmt "\n", __FILE__, __LINE__, __FUNCTION__, ## args); }

#define W(fmt, args...) \
    { printk(KERN_WARNING "W : [File] : %s; [Line] : %d; [Func] : %s(); " fmt "\n", __FILE__, __LINE__, __FUNCTION__, ## args); }

#define E(fmt, args...) \
    { printk(KERN_ERR "E : [File] : %s; [Line] : %d; [Func] : %s(); " fmt "\n", __FILE__, __LINE__, __FUNCTION__, ## args); }

/*-------------------------------------------------------*/

/** ʹ�� D(), ��ʮ���Ƶ���ʽ��ӡ���� 'var' �� value. */
#define D_DEC(var)  D(#var " = %d.", var);

#define E_DEC(var)  E(#var " = %d.", var);

/** ʹ�� D(), ��ʮ�����Ƶ���ʽ��ӡ���� 'var' �� value. */
#define D_HEX(var)  D(#var " = 0x%x.", var);

#define E_HEX(var)  E(#var " = 0x%x.", var);

/** ʹ�� D(), ��ʮ�����Ƶ���ʽ ��ӡָ�����ͱ��� 'ptr' �� value. */
#define D_PTR(ptr)  D(#ptr " = %p.", ptr);

#define E_PTR(ptr)  E(#ptr " = %p.", ptr);

/** ʹ�� D(), ��ӡ char �ִ�. */
#define D_STR(pStr) \
{\
    if ( NULL == pStr )\
    {\
        D(#pStr" = NULL.");\
    }\
    else\
    {\
        D(#pStr" = '%s'.", pStr);\
    }\
}

#define E_STR(pStr) \
{\
    if ( NULL == pStr )\
    {\
        E(#pStr" = NULL.");\
    }\
    else\
    {\
        E(#pStr" = '%s'.", pStr);\
    }\
}

#ifdef ENABLE_DEBUG_LOG
/**
 * log �� 'pStart' ��ַ��ʼ�� 'len' ���ֽڵ�����. 
 */
#define D_MEM(pStart, len) \
    {\
        int i = 0;\
        char* p = (char*)pStart;\
        D("dump memory from addr of '" #pStart "', from %p, length %d' : ", pStart, len); \
        printk("\t\t");\
        for ( i = 0; i < len ; i++ )\
        {\
            printk("0x%02x, ", p[i] );\
        }\
        printk("\n");\
    }
#else
#define  D_MEM(...)  ((void)0)
#endif

/*-------------------------------------------------------*/

#define EXIT_FOR_DEBUG \
{\
    E("To exit for debug.");\
    return 1;\
}

/*-------------------------------------------------------*/

/**
 * ���ú���, ����鷵��ֵ, ���ݷ���ֵ�����Ƿ���ת��ָ���Ĵ��������. 
 * @param functionCall
 *          ���ض������ĵ���, �ú����ķ���ֵ������ ���� �ɹ� or err �� ������. 
 *          ����, �����ú��� "����" �Ǳ�����Ϊ "���� 0 ��ʾ�����ɹ�". 
 * @param result
 *		    ���ڼ�¼�������ص� error code �� ���ͱ���, ͨ���� "ret" or "result" ��.
 * @param label
 *		    ���������ش���, ����Ҫ��ת���� �������� ���, ͨ������ "EXIT". 
 */
#define CHECK_FUNC_CALL(functionCall, result, label) \
{\
	if ( 0 != ( (result) = (functionCall) ) )\
	{\
		E("Function call returned error : " #result " = %d.", result);\
		goto label;\
	}\
}

/**
 * ���ض�������, �ж� error ����, �Ա��� 'retVar' ���� 'errCode', 
 * Log �����Ӧ�� Error Caution, Ȼ����ת 'label' ָ���Ĵ��봦ִ��. 
 * @param msg
 *          ���ִ���ʽ����ʾ��Ϣ. 
 * @param retVar
 *		    ��ʶ����ִ��״̬���߽���ı���, �������þ���� Error Code. 
 *		    ͨ���� 'ret' or 'result'. 
 * @param errCode
 *          �����ض� error �ĳ�����ʶ, ͨ���� �����̬. 
 * @param label
 *          ����Ҫ��ת���Ĵ��������ı��, ͨ������ 'EXIT'. 
 * @param args...
 *          ��Ӧ 'msgFmt' ʵ���� '%s', '%d', ... �� ת��˵���� �ľ���ɱ䳤ʵ��. 
 */
#define SET_ERROR_AND_JUMP(msgFmt, retVar, errCode, label, args...) \
{\
    E("To set '" #retVar "' to %d('" #errCode "'), because : " msgFmt, (errCode), ## args);\
	(retVar) = (errCode);\
	goto label;\
}


/* ---------------------------------------------------------------------------------------------------------
 *  Types and Structures Definition
 * ---------------------------------------------------------------------------------------------------------
 */


/* ---------------------------------------------------------------------------------------------------------
 *  Global Functions' Prototype
 * ---------------------------------------------------------------------------------------------------------
 */


/* ---------------------------------------------------------------------------------------------------------
 *  Inline Functions Implementation 
 * ---------------------------------------------------------------------------------------------------------
 */

#ifdef __cplusplus
}
#endif

#endif /* __CUSTOM_LOG_H__ */

