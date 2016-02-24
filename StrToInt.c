/**********************************************************************
* 版权所有 (C)2016, Zhou Zhaoxiong。
*
* 文件名称： StrToInt.c
* 文件标识： 无
* 内容摘要： 将字符串转换为整数
* 其它说明： 例如, 将"123"转换为123
* 当前版本： V1.0
* 作    者： Zhou Zhaoxiong
* 完成日期： 20160218
*
**********************************************************************/
#include <stdio.h>
#include <limits.h>   // 由于在代码中使用了INT_MAX, 因此要包含该头文件


// 重新定义数据类型
typedef signed   char  INT8;
typedef          int   INT32;
typedef unsigned int   UINT32;


// 函数声明
INT32 CalIntVal(INT32 iBitLen);
INT32 JudgeIfOverFlow(INT8 *pszTestStr);


/**********************************************************************
* 功能描述： 主函数
* 输入参数： 无
* 输出参数： 无
* 返 回 值： 0-执行成功   其它-执行失败
* 其它说明： 无
* 修改日期        版本号     修改人            修改内容
* ---------------------------------------------------------------------
* 20160218        V1.0     Zhou Zhaoxiong        创建
***********************************************************************/
INT32 main()
{
    INT8   szInputStr[100] = {0};
    INT8   szTestStr[100]  = {0};
    INT32  iResultInt      = 0;    // 转换之后的整数最大支持2147483647
    UINT32 iPosFlag        = 0;
    UINT32 iTestStrLen     = 0;
    UINT32 iBitVal         = 0;
    INT32  iRetVal         = 0;

    printf("Max value of int is %d\n", INT_MAX);   // 求出int的最大值
    
    printf("Please input the string: \n");
    scanf("%s", szInputStr);
    printf("InputStr=%s\n", szInputStr);

    // 判断输入的字符串中是否有除数字之外的其它字符, 若有, 则直接退出
    for (iPosFlag = 0; iPosFlag < strlen(szInputStr); iPosFlag ++)
    {
        if (szInputStr[iPosFlag] < '0' || szInputStr[iPosFlag] > '9')
        {
            printf("%s is not a digital string, please check!\n", szInputStr);
            return -1;
        }
    }

    // 如果字符串前面有字符0, 则将其去掉
    iPosFlag = 0;
    while (szInputStr[iPosFlag] == '0')
    {
        iPosFlag ++;
    }

    // 获取去除0之后的字符串值
    strncpy(szTestStr, szInputStr+iPosFlag, strlen(szInputStr)-iPosFlag);

    // 判断字符串是否大于2147483647, 若是, 则直接退出
    iRetVal = JudgeIfOverFlow(szTestStr);
    if (iRetVal != 0)
    {
        printf("%s is bigger than INT_MAX(2147483647), please check!\n", szTestStr);
        return -1;
    }
    
    // 计算字符串对应的整数值
    iTestStrLen = strlen(szTestStr);
    iResultInt = 0;
    for (iPosFlag = 0; iPosFlag < iTestStrLen; iPosFlag ++)
    {
        iBitVal = szTestStr[iPosFlag] - '0';    // 计算每一位对应的数字
        iResultInt = iResultInt + iBitVal * CalIntVal(iTestStrLen-iPosFlag);
    }

    printf("ResultInt=%d\n", iResultInt);
    
    return 0;            
}


/**********************************************************************
* 功能描述： 判断输入的字符串是否溢出
* 输入参数： pszTestStr-测试字符串
* 输出参数： 无
* 返 回 值： 1-溢出  0-未溢出
* 其它说明： 判断字符串是否大于2147483647, 若是, 则溢出
* 修改日期          版本号         修改人          修改内容
* ---------------------------------------------------------------
* 20160218          V1.0       Zhou Zhaoxiong        创建
***********************************************************************/
INT32 JudgeIfOverFlow(INT8 *pszTestStr)
{
    UINT32 iTestStrLen         = 0;
    INT8   szProcessedStr[100] = {0};
    INT8   szMaxValOfInt[100]  = {0};

    snprintf(szMaxValOfInt, sizeof(szMaxValOfInt)-1, "%d", INT_MAX);   // 求出int的最大值

    iTestStrLen = strlen(pszTestStr);

    if (iTestStrLen > strlen(szMaxValOfInt))         // 长度超过
    {
        return 1;
    }
    else if (iTestStrLen == strlen(szMaxValOfInt))   // 长度相等
    {
        if (strcmp(pszTestStr, szMaxValOfInt) > 0)   // 溢出
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else     // 测试字符串长度小于"2147483647"的长度, 未溢出
    {
        return 0;
    }
}



/**********************************************************************
* 功能描述： 求字符串中的每一位所对应的整数值
* 输入参数： iBitLen-对应整数的第多少位
* 输出参数： 无
* 返 回 值： 该位所对应的整数值
* 其它说明： 无
* 修改日期          版本号         修改人          修改内容
* ---------------------------------------------------------------
* 20160218          V1.0       Zhou Zhaoxiong        创建
***********************************************************************/
INT32 CalIntVal(INT32 iBitLen)
{    
    if (iBitLen == 1)   // 个位
    {
        return 1;
    }
    else
    {
        return 10 * CalIntVal(iBitLen-1);
    }
}
