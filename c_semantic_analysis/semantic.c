#include "type.h"
float atof();
void semantic_analysis(A_NODE *);
void set_literal_address(A_NODE *);
int put_literal(A_LITERAL, int);
void sem_program(A_NODE *);
A_TYPE *sem_expression(A_NODE *);
int sem_statement(A_NODE *, int, A_TYPE *, BOOLEAN, BOOLEAN, BOOLEAN);
int sem_statement_list(A_NODE *, int, A_TYPE *, BOOLEAN, BOOLEAN, BOOLEAN);
void
int
int
int
void
A_ID
A_ID
A_NODE *convertScalarToInteger(A_NODE *);
A_NODE *convertUsualAssignmentConversion(A_TYPE *, A_NODE *); A_NODE *convertUsualUnaryConversion(A_NODE *);
sem_for_expression(A_NODE *); sem_A_TYPE(A_TYPE *) ; sem_declaration_list(A_ID *, int); sem_declaration(A_ID *,int); sem_arg_expr_list(A_NODE *, A_ID *);
*getStructFieldIdentifier(A_TYPE *, char *); *getPointerFieldIdentifier(A_TYPE *, char *);
A_TYPE *convertUsualBinaryConversion(A_NODE *);
A_NODE *convertCastingConversion(A_NODE *,A_TYPE *);
BOOLEAN isAllowableAssignmentConversion(A_TYPE *, A_TYPE *, A_NODE *); BOOLEAN isAllowableCastingConversion(A_TYPE *, A_TYPE *);
BOOLEAN isModifiableLvalue(A_NODE *);
BOOLEAN isConstantZeroExp(A_NODE *);
BOOLEAN isSameParameterType(A_ID *, A_ID *);
BOOLEAN isNotSameType(A_TYPE *, A_TYPE *);
BOOLEAN isCompatibleType(A_TYPE *, A_TYPE *);
BOOLEAN isCompatiblePointerType(A_TYPE *, A_TYPE *);
BOOLEAN isIntType(A_TYPE *);
//

BOOLEAN isFloatType(A_TYPE *);
BOOLEAN isArithmeticType(A_TYPE *);
BOOLEAN isAnyIntegerType(A_TYPE *);
BOOLEAN isIntegralType(A_TYPE *);
BOOLEAN isStructOrUnionType(A_TYPE *);
BOOLEAN isFunctionType(A_TYPE *);
BOOLEAN isScalarType(A_TYPE *);
BOOLEAN isPointerType(A_TYPE *);
BOOLEAN isPointerOrArrayType(A_TYPE *);
BOOLEAN isArrayType(A_TYPE *);
BOOLEAN isStringType(A_TYPE *);
BOOLEAN isVoidType(A_TYPE *);
A_LITERAL checkTypeAndConvertLiteral(A_LITERAL,A_TYPE*, int); A_LITERAL getTypeAndValueOfExpression(A_NODE *);
A_TYPE
A_TYPE
void
void
void
A_NODE *makeNode(NODE_NAME, A_NODE *, A_NODE *,A_NODE *); extern A_TYPE *int_type, *float_type, *char_type, *string_type, *void_type; int global_address=12;
int semantic_err=0;
#define LIT_MAX 100
A_LITERAL literal_table[LIT_MAX];
int literal_no=0;
int literal_size=0;
void semantic_analysis(A_NODE *node) {
sem_program(node); set_literal_address(node);
}
void set_literal_address(A_NODE *node) {
*setTypeElementType(A_TYPE *,A_TYPE *); *makeType(T_KIND);
setTypeSize(A_TYPE *,int); semantic_warning(int, int); semantic_error();
//

int i;
for (i=1;i<=literal_no; i++)
literal_table[i].addr+=node->value; node->value+=literal_size;
}
void sem_program(A_NODE *node) {
int i; switch(node->name) {
} }
case N_PROGRAM : i=sem_declaration_list(node->clink,12); node->value=global_address;
break;
default : semantic_error(90,node->line); break;
int put_literal(A_LITERAL lit, int ll) {
float ff;
if (literal_no >=LIT_MAX)
semantic_error(93, ll);
else
literal_no++; literal_table[literal_no]=lit;
literal_table[literal_no].addr=literal_size; if (lit.type->kind==T_ENUM)
literal_size+=4;
else if (isStringType(lit.type))
literal_size+=strlen(lit.value.s)+1; if (literal_size%4)
literal_size=literal_size/4*4+4; return(literal_no);
//

}
A_TYPE *sem_expression(A_NODE *node) {
A_TYPE *result=NIL, *t,*t1, *t2; A_ID *id;
A_LITERAL lit;
int i;
BOOLEAN lvalue=FALSE;; switch(node->name) {
case N_EXP_IDENT : id=node->clink;
switch (id->kind) { case ID_VAR:
}
case ID_PARM: result=id->type;
// lvalue 여부 판단 ??????
break;
case ID_FUNC: result=id->type;
break;
case ID_ENUM_LITERAL:
result=int_type;
break;
default: semantic_error(38,node->line,id->name);
break;
break;
case N_EXP_INT_CONST :
result=int_type;
break;
case N_EXP_FLOAT_CONST :
lit.type=float_type; lit.value.f=atof(node->clink);
//

node->clink=put_literal(lit,node->line); result = float_type;
break;
case N_EXP_CHAR_CONST : result=char_type;
break;
case N_EXP_STRING_LITERAL :
lit.type=string_type; lit.value.s=node->clink; node->clink=put_literal(lit,node->line); result=string_type;
break;
case N_EXP_ARRAY :
t1=sem_expression(node->llink); t2=sem_expression(node->rlink);
// usual binary conversion t=convertUsualBinaryConversion(node); // 배열참조식의 좌우측 타입을 검사 ??????
??????
// 수식의 lvalue 여부 판단 ??????
??????
break;
// index of literal table
case N_EXP_STRUCT :
t=sem_expression(node->llink); id=getStructFieldIdentifier(t,node->rlink);
// 구조체참조식의 좌우측 타입을 검사하고 수식의 lvalue 여부 판단 ??????
??????
node->rlink=id;
break;
case N_EXP_ARROW: t=sem_expression(node->llink);
//
// index of literal table

id=getPointerFieldIdentifier(t,node->rlink);
// 구조체포인터참조식의 좌우측 타입을 검사하고 lvalue 여부 판단 ??????
??????
node->rlink=id;
break;
case N_EXP_FUNCTION_CALL : t=sem_expression(node->llink);
// usual unary conversion node->llink=convertUsualUnaryConversion(node->llink); t=node->llink->type;
// 함수호출식의 좌측이 함수 타입인지 검사하고
// 매개변수의 갯수와 타입도 검사
??????
??????
break;
case N_EXP_POST_INC : case N_EXP_POST_DEC :
result=sem_expression(node->clink);
// usual binary conversion between the expression and 1 // 수식의 타입 검사
?????
?????
// check if modifiable lvalue
if (!isModifiableLvalue(node->clink))
semantic_error(60,node->line); break;
case N_EXP_CAST : result=node->llink;
i=sem_A_TYPE(result); t=sem_expression(node->rlink);
// check allowable casting conversion ?????
?????
//

break;
case N_EXP_SIZE_TYPE :
t=node->clink;
i=sem_A_TYPE(t);
// check if incomplete array, function, void if ( ????? )
semantic_error(39,node->line);
else
node->clink=i; result=int_type;
break;
case N_EXP_SIZE_EXP :
t=sem_expression(node->clink);
// check if incomplete array, function if ( ????? )
semantic_error(39,node->line);
else
node->clink=t->size; result=int_type;
break;
case N_EXP_PLUS :
case N_EXP_MINUS : t=sem_expression(node->clink); // 수식의 타입 검사, 변환 ?????
?????
break;
case N_EXP_NOT : t=sem_expression(node->clink); // 수식의 타입 검사, 변환 ?????
?????
break;
case N_EXP_AMP :
//

t=sem_expression(node->clink); // 수식의 타입 검사, 결정 ?????
?????
break;
case N_EXP_STAR :
t=sem_expression(node->clink); node->clink=convertUsualUnaryConversion(node->clink); // 수식의 타입 검사, 결정, lavalue 여부 판단
?????
?????
break;
case N_EXP_PRE_INC : case N_EXP_PRE_DEC :
result=sem_expression(node->clink);
// usual binary conversion between the expression and 1 // 수식의 타입 검사
?????
?????
// check if modifiable lvalue
if (!isModifiableLvalue(node->clink))
semantic_error(60,node->line); break;
case N_EXP_MUL : case N_EXP_DIV :
t1=sem_expression(node->llink); t2=sem_expression(node->rlink); // 좌우 수식의 타입 검사와 변환 ?????
?????
break;
case N_EXP_MOD :
t1=sem_expression(node->llink); t2=sem_expression(node->rlink);
//

// 좌우 수식의 타입 검사와 변환 ?????
?????
result=int_type;
break;
case N_EXP_ADD :
t1=sem_expression(node->llink); t2=sem_expression(node->rlink); // 좌우 수식의 타입 검사와 변환 ?????
?????
break;
case N_EXP_SUB :
t1=sem_expression(node->llink); t2=sem_expression(node->rlink); // 좌우 수식의 타입 검사와 변환 ?????
?????
break;
case N_EXP_LSS : case N_EXP_GTR : case N_EXP_LEQ :
case N_EXP_GEQ : t1=sem_expression(node->llink); t2=sem_expression(node->rlink); // 좌우 수식의 타입 검사와 변환 ?????
?????
result=int_type;
break;
case N_EXP_NEQ : case N_EXP_EQL :
t1=sem_expression(node->llink); t2=sem_expression(node->rlink);
//

// 좌우 수식의 타입 검사와 변환 ?????
?????
result=int_type;
break;
case N_EXP_AND :
case N_EXP_OR : t=sem_expression(node->llink);
// 좌우 수식의 타입 검사와 변환 ?????
?????
result=int_type;
break;
case N_EXP_ASSIGN : result=sem_expression(node->llink); // check if modifiable lvalue
if (!isModifiableLvalue(node->llink))
semantic_error(60,node->line); // 좌우 수식의 타입 검사와 변환
????? ????? break;
default : semantic_error(90,node->line); break;
} node->type=result; node->value=lvalue; return (result);
}
// check argument-expression-list in function call expression void sem_arg_expr_list(A_NODE *node, A_ID *id)
{
A_TYPE *t;


A_ID *a;
int arg_size=0; switch(node->name) {
case N_ARG_LIST : if (id==0)
semantic_error(34,node->line); else {
if (id->type) {
t=sem_expression(node->llink); node->llink=convertUsualUnaryConversion(node->llink);
if (isAllowableCastingConversion(id->type,node->llink->type))
node->llink=convertCastingConversion(node->llink,id->type); else
semantic_error(59,node->line); sem_arg_expr_list(node->rlink,id->link);}
else { // DOTDOT parameter : no conversion t=sem_expression(node->llink); sem_arg_expr_list(node->rlink,id); }
arg_size=node->llink->type->size+node->rlink->value;} break;
case N_ARG_LIST_NIL :
if (id && id->type) // check if '...' argument
semantic_error(35,node->line); break;
default : semantic_error(90,node->line); break;
}
if (arg_size%4) arg_size=arg_size/4*4+4; node->value=arg_size;
}
BOOLEAN isModifiableLvalue(A_NODE *node) {
if (node->value==FALSE||isVoidType(node->type)||isFunctionType(node->type))


return (FALSE); else
return (TRUE);
}
// check statement and return local variable size
int sem_statement(A_NODE *node, int addr, A_TYPE *ret, BOOLEAN sw, BOOLEAN
{
brk, BOOLEAN cnt)
int local_size=0,i; A_LITERAL lit;
A_TYPE *t; switch(node->name) {
case N_STMT_LABEL_CASE : if (sw==FALSE)
semantic_error(71,node->line); lit=getTypeAndValueOfExpression(node->llink);
// 상수수식의 타입검사, 상수값 저장
?????
????? local_size=sem_statement(node->rlink,addr,?????????????????); break;
case N_STMT_LABEL_DEFAULT :
// 명령문 사용가능 여부 판단
?????
????? local_size=sem_statement(node->clink,addr,?????????????????); break;
case N_STMT_COMPOUND: if(node->llink)
local_size=sem_declaration_list(node->llink,addr); local_size+=sem_statement_list(
node->rlink,local_size+addr,ret,sw,brk,cnt); break;
case N_STMT_EMPTY:


break;
case N_STMT_EXPRESSION:
t=sem_expression(node->clink);
break;
case N_STMT_IF:
t=sem_expression(node->llink);
// 수식의 타입 검사
?????
????? local_size=sem_statement(node->rlink,addr,???????????????);; break;
case N_STMT_IF_ELSE:
t=sem_expression(node->llink);
// 수식의 타입 검사
?????
????? local_size=sem_statement(node->clink,addr,?????????????????); i=sem_statement(node->rlink,addr,?????????????????????);
// 명령문 내부 선언문의 크기 결정
?????
break;
case N_STMT_SWITCH:
t=sem_expression(node->llink);
// 수식의 타입 검사
?????
????? local_size=sem_statement(node->rlink,addr,???????????????); break;
case N_STMT_WHILE:
t=sem_expression(node->llink);
// 수식의 타입 검사
?????
????? local_size=sem_statement(node->rlink,addr,???????????????????);


break;
case N_STMT_DO:
local_size=sem_statement(node->llink,addr,?????????????????????); t=sem_expression(node->rlink);
// 수식의 타입 검사
?????
?????
break;
case N_STMT_FOR:
sem_for_expression(node->llink); local_size=sem_statement(node->rlink,addr,???????????????????????); break;
case N_STMT_CONTINUE:
// 명령문 사용가능 여부 판단 ?????
?????
break;
case N_STMT_BREAK:
// 명령문 사용가능 여부 판단 ?????
?????
break;
case N_STMT_RETURN: if(node->clink){
t=sem_expression(node->clink); // 수식의 리턴 타입 분석
?????
break; default:
semantic_error(90,node->line);
break; }
node->value=local_size; return(local_size);


}
void sem_for_expression(A_NODE *node) {
A_TYPE *t;
switch (node->name) {
} }
case N_FOR_EXP : if(node->llink)
t=sem_expression(node->llink); if(node->clink) {
t=sem_expression(node->clink); // 수식의 타입 검사
?????
?????
} if(node->rlink)
t=sem_expression(node->rlink); break;
default : semantic_error(90,node->line); break;
// check statement-list and return local variable size
int sem_statement_list(A_NODE *node, int addr, A_TYPE *ret, BOOLEAN sw,
BOOLEAN brk, BOOLEAN cnt)
{
int size,i;
switch(node->name) { case N_STMT_LIST:
size=sem_statement(node->llink, ?????????????????????); i=sem_statement_list(node->rlink, ?????????????????????); if(size<i)
size=i;


break;
case N_STMT_LIST_NIL:
size=0;
break; default :
semantic_error(90,node->line); break;
} node->value=size; return(size);
}
// check type and return its size (size of incomplete type is 0) int sem_A_TYPE(A_TYPE *t)
{
A_ID *id; A_TYPE *tt; A_LITERAL lit; int result=0,i; if (t->check)
return(t->size); t->check=1;
switch (t->kind) { case T_NULL:
semantic_error(80,t->line);
break; case T_ENUM:
i=0; id=t->field; while (id) {
// enumerator 들의 값계산 저장
// 초기화수식이 있는 경우 수식의 값과 타입 검사 ?????
?????


} result=4;
break; case T_ARRAY:
if (t->expr){
// 배열 크기 수식 계산 검사 저장
????? ????? }
result=sem_A_TYPE(t->element_type)*(int)t->expr; // 배열의 원소 타입 검사
?????
?????
break; case T_STRUCT:
id=t->field; while (id) {
result+=sem_declaration(id, ????????????);
id = id->link; } break;
case T_UNION: id=t->field; while (id) {
break; case T_FUNC:
tt=t->element_type; i=sem_A_TYPE(tt);
// check return type ?????
?????
i=sem_declaration(id,????????????); if (i>result)
result=i; id = id->link; }


i=sem_declaration_list(t->field,12)+12; // parameter type and size if (t->expr) { // skip prototype declaration
i=i+sem_statement(t->expr,i,?????????????????????????????????);} t->local_var_size=i;
break;
case T_POINTER: i=sem_A_TYPE(t->element_type); result=4;
break;
case T_VOID: break;
default: semantic_error(90,t->line); break;
} t->size=result; return(result);
}
// set variable address in declaration-list, and return its total variable size int sem_declaration_list(A_ID *id, int addr)
{
int i=addr; while (id) {
addr+=sem_declaration(id,addr); id=id->link;
} return(addr-i);
}
// check declaration (identifier), set address, and return its size int sem_declaration(A_ID *id,int addr)
{
A_TYPE *t;
int size=0,i; A_LITERAL lit; switch (id->kind) {


case ID_VAR:
i=sem_A_TYPE(id->type);
// check empty array
if (isArrayType(id->type) && id->type->expr==NIL)
semantic_error(86,id->line); if (i%4) i=i/4*4+4;
if (id->specifier==S_STATIC) id->level=0;
if (id->level==0) { id->address=global_address;
global_address+=i;} else {
id->address=addr;
size=i; } break;
case ID_FIELD: i=sem_A_TYPE(id->type); // 필드의 타입 검사 ?????
?????
if (i%4)
i=i/4*4+4; id->address=addr;
size=i;
break; case ID_FUNC:
i=sem_A_TYPE(id->type);
break; case ID_PARM:
if (id->type){ size=sem_A_TYPE(id->type);
// usual unary conversion of parm type ?????
?????


break; case ID_TYPE:
return(id);
size=id->type->size; if (size%4)
size=size/4*4+4; id->address=addr;}
i=sem_A_TYPE(id->type);
break; default:
semantic_error(89,id->line,id->name);
break; }
return (size);
}
A_ID *getStructFieldIdentifier(A_TYPE *t, char *s) {
A_ID *id=NIL;
if (isStructOrUnionType(t)) {
id=t->field; while (id) {
if (strcmp(id->name,s)==0) break;
id=id->link;} }
}
A_ID *getPointerFieldIdentifier(A_TYPE *t, char *s) {
A_ID *id=NIL;
if (t && t->kind==T_POINTER) {
t=t->element_type;
if (isStructOrUnionType(t)){
id=t->field; while (id) {
if (strcmp(id->name,s)==0)


}
return(id);
}
BOOLEAN isSameParameterType(A_ID *a, A_ID *b) {
while (a) {
if (b==NIL || isNotSameType(a->type,b->type))
return (FALSE); a=a->link;
b=b->link;} if (b)
else
return (FALSE);
return (TRUE);
break; id=id->link;} } }
}
BOOLEAN isCompatibleType(A_TYPE *t1, A_TYPE *t2) {
if (isArrayType(t1) && isArrayType(t2))
if (t1->size==0 || t2->size==0 || t1->size==t2->size)
return(isCompatibleType(t1->element_type,t2->element_type)); else
return(FALSE);
else if (isFunctionType(t1) && isFunctionType(t2))
if (isSameParameterType(t1->field,t2->field)) return(isCompatibleType(t1->element_type,t2->element_type));
else
return (FALSE);
else if (isPointerType(t1) && isPointerType(t2)) return(isCompatibleType(t1->element_type,t2->element_type));
else
return(t1==t2);
BOOLEAN isConstantZeroExp(A_NODE *node)


{
if (node->name==N_EXP_INT_CONST && node->clink==0) return (TRUE);
else
return (FALSE);
}
BOOLEAN isCompatiblePointerType(A_TYPE *t1, A_TYPE *t2) {
if (isPointerType(t1) && isPointerType(t2)) return(isCompatibleType(t1->element_type,t2->element_type));
else
return(FALSE);
}
A_NODE *convertScalarToInteger(A_NODE *node) {
if (isFloatType(node->type)) { semantic_warning(16,node->line);
node=makeNode(N_EXP_CAST,int_type,NIL,node); } node->type=int_type;
return(node);
}
A_NODE *convertUsualAssignmentConversion(A_TYPE *t1, A_NODE *node) {
A_TYPE *t2;
t2=node->type;
if (!isCompatibleType(t1,t2)) {
semantic_warning(11,node->line); node=makeNode(N_EXP_CAST,t1,NIL,node); node->type=t1;}
return (node);
}
A_NODE *convertUsualUnaryConversion(A_NODE *node) {
A_TYPE *t;


t=node->type;
if (t==char_type) {
t=int_type; node=makeNode(N_EXP_CAST,t,NIL,node); node->type=t;}
else if (isArrayType(t)){ t=setTypeElementType(makeType(T_POINTER),t->element_type); t->size=4;
node=makeNode(N_EXP_CAST,t,NIL,node);
node->type=t;}
else if (isFunctionType(t)){ t=setTypeElementType(makeType(T_POINTER),t); t->size=4; node=makeNode(N_EXP_AMP,NIL,node,NIL); node->type=t;}
return (node);
}
A_TYPE *convertUsualBinaryConversion(A_NODE *node) {
A_TYPE *t1, *t2, *result=NIL; t1=node->llink->type; t2=node->rlink->type;
if(isFloatType(t1) && !isFloatType(t2)) {
semantic_warning(14,node->line); node->rlink=makeNode(N_EXP_CAST,t1,NIL,node->rlink); node->rlink->type=t1;
result=t1;}
else if(!isFloatType(t1) && isFloatType(t2)) { semantic_warning(14,node->line);
node->llink=makeNode(N_EXP_CAST,t2,NIL,node->llink); node->llink->type=t2;
result=t2;}
else if (t1==t2) result=t1;


else
result=int_type; return (result);
}
A_NODE *convertCastingConversion(A_NODE *node,A_TYPE *t1) {
A_TYPE *t2;
t2=node->type;
if (!isCompatibleType(t1,t2)) {
semantic_warning(12,node->line); node=makeNode(N_EXP_CAST,t1,NIL,node); node->type=t1;}
return (node);
}
BOOLEAN isAllowableAssignmentConversion(A_TYPE *t1, A_TYPE *t2, A_NODE
{
*node) // t1 <// t2
if (isArithmeticType(t1) && isArithmeticType(t2)) return (TRUE);
else if (isStructOrUnionType(t1) && isCompatibleType(t1,t2)) return (TRUE);
else if (isPointerType(t1) && (isConstantZeroExp(node) || isCompatiblePointerType(t1,t2)))
else
return (TRUE);
return (FALSE);
}
BOOLEAN isAllowableCastingConversion(A_TYPE *t1, A_TYPE *t2) {
// t1 <// t2
if (isAnyIntegerType(t1) && (isAnyIntegerType(t2) || isFloatType(t2) || isPointerType(t2)))
return (TRUE);
else if (isFloatType(t1) && isArithmeticType(t2))
return (TRUE);


else if (isPointerType(t1) && (isAnyIntegerType(t2) || isPointerType(t2))) return (TRUE);
else if (isVoidType(t1)) return (TRUE);
else
return (FALSE);
}
BOOLEAN isFloatType(A_TYPE *t) {
if (t ==float_type) return(TRUE);
else
return(FALSE);
}
BOOLEAN isArithmeticType(A_TYPE *t) {
if (t && t->kind==T_ENUM) return(TRUE);
else
return(FALSE);
}
BOOLEAN isScalarType(A_TYPE *t) {
if (t && ((t->kind==T_ENUM) || (t->kind==T_POINTER))) return(TRUE);
else
return(FALSE);
}
BOOLEAN isAnyIntegerType(A_TYPE *t) {
if ( t && (t==int_type || t==char_type)) return(TRUE);
else
return(FALSE);


}
BOOLEAN isIntegralType(A_TYPE *t) {
if ( t && t->kind==T_ENUM && t!=float_type) return(TRUE);
else
return(FALSE);
}
BOOLEAN isFunctionType(A_TYPE *t) {
if (t && t->kind==T_FUNC) return(TRUE);
else
return(FALSE);
}
BOOLEAN isStructOrUnionType(A_TYPE *t) {
if (t && (t->kind==T_STRUCT || t->kind==T_UNION)) return(TRUE);
else
return(FALSE);
}
BOOLEAN isPointerType(A_TYPE *t) {
if (t && t->kind==T_POINTER) return(TRUE);
else
return(FALSE);
}
BOOLEAN isPointerOrArrayType(A_TYPE *t) {
if (t && ( t->kind==T_POINTER || t->kind == T_ARRAY)) return(TRUE);
else


return(FALSE);
}
BOOLEAN isIntType(A_TYPE *t) {
if (t && t==int_type) return(TRUE);
else
return(FALSE);
}
BOOLEAN isVoidType(A_TYPE *t) {
if (t && t==void_type) return(TRUE);
else
return(FALSE);
}
BOOLEAN isArrayType(A_TYPE *t) {
if (t && t->kind==T_ARRAY) return(TRUE);
else
return(FALSE);
}
BOOLEAN isStringType(A_TYPE *t) {
if (t && (t->kind==T_POINTER||t->kind==T_ARRAY) && t->element_type==char_type)
else
return(TRUE);
return(FALSE);
}
// convert literal type
A_LITERAL checkTypeAndConvertLiteral(A_LITERAL result,A_TYPE *t, int ll) {


if (result.type==int_type && t==int_type || result.type==char_type && t==char_type || result.type==float_type && t==float_type ) ;
else if (result.type==int_type && t==float_type){ result.type=float_type;
result.value.f=result.value.i;}
else if (result.type==int_type && t==char_type){
result.type=char_type;
result.value.c=result.value.i;}
else if (result.type==float_type && t==int_type){
result.type=int_type;
result.value.i=result.value.f;}
else if (result.type==char_type && t==int_type){
result.type=int_type; result.value.i=result.value.c;}
else
semantic_error(41,ll); return (result);
}
A_LITERAL getTypeAndValueOfExpression(A_NODE *node) {
A_TYPE *t;
A_ID *id;
A_LITERAL result,r; result.type=NIL; switch(node->name) {
case N_EXP_IDENT : id=node->clink;
if (id->kind!=ID_ENUM_LITERAL) semantic_error(19,node->line,id->name);
else {
result.type=int_type;
result.value.i=id->init;} break;


case N_EXP_INT_CONST : result.type=int_type;
result.value.i=(int)node->clink;
break;
case N_EXP_CHAR_CONST :
result.type=char_type; result.value.c=(char)node->clink; break;
case N_EXP_FLOAT_CONST : result.type=float_type;
result.value.f=atof(node->clink);
break;
case N_EXP_STRING_LITERAL : case N_EXP_ARRAY :
case N_EXP_FUNCTION_CALL : case N_EXP_STRUCT :
case N_EXP_ARROW :
case N_EXP_POST_INC :
case N_EXP_PRE_INC :
case N_EXP_POST_DEC :
case N_EXP_PRE_DEC :
case N_EXP_AMP :
case N_EXP_STAR :
case N_EXP_NOT :
semantic_error(18,node->line);
break;
case N_EXP_MINUS :
result=getTypeAndValueOfExpression(node->clink); if (result.type==int_type)
result.value.i=-result.value.i; else if (result.type==float_type)
else
result.value.f=-result.value.f; semantic_error(18,node->line);


break;
case N_EXP_SIZE_EXP :
t=sem_expression(node->clink); result.type=int_type; result.value.i=t->size;
break;
case N_EXP_SIZE_TYPE : result.type=int_type;
result.value.i=sem_A_TYPE(node->clink);
break;
case N_EXP_CAST :
result=getTypeAndValueOfExpression(node->rlink); result=checkTypeAndConvertLiteral(
result,(A_TYPE*)node->llink,node->line); break;
case N_EXP_MUL : result=getTypeAndValueOfExpression(node->llink); r=getTypeAndValueOfExpression(node->rlink);
if (result.type==int_type && r.type==int_type){
result.type=int_type;
result.value.i=result.value.i*r.value.i;}
else if (result.type==int_type && r.type==float_type){
result.type=float_type;
result.value.f=result.value.i*r.value.f;}
else if (result.type==float_type && r.type==int_type){
result.type=float_type;
result.value.f=result.value.f*r.value.i;}
else if (result.type==float_type && r.type==float_type){
result.type=float_type; result.value.f=result.value.f*r.value.f;}
else
semantic_error(18,node->line); break;
case N_EXP_DIV :


result=getTypeAndValueOfExpression(node->llink); r=getTypeAndValueOfExpression(node->rlink);
if (result.type==int_type && r.type==int_type){
result.type=int_type;
result.value.i=result.value.i/r.value.i;}
else if (result.type==int_type && r.type==float_type){
result.type=float_type;
result.value.f=result.value.i/r.value.f;}
else if (result.type==float_type && r.type==int_type){
result.type=float_type;
result.value.f=result.value.f/r.value.i;}
else if (result.type==float_type && r.type==float_type){
result.type=float_type; result.value.f=result.value.f/r.value.f;}
else
semantic_error(18,node->line); break;
case N_EXP_MOD : result=getTypeAndValueOfExpression(node->llink); r=getTypeAndValueOfExpression(node->rlink);
if (result.type==int_type && r.type==int_type)
result.value.i=result.value.i%r.value.i;
else
semantic_error(18,node->line); break;
case N_EXP_ADD : result=getTypeAndValueOfExpression(node->llink); r=getTypeAndValueOfExpression(node->rlink);
if (result.type==int_type && r.type==int_type){
result.type=int_type;
result.value.i=result.value.i+r.value.i;}
else if (result.type==int_type && r.type==float_type){
result.type=float_type; result.value.f=result.value.i+r.value.f;}


else if
else if
else
semantic_error(18,node->line); break;
case N_EXP_SUB : result=getTypeAndValueOfExpression(node->llink); r=getTypeAndValueOfExpression(node->rlink);
if (result.type==int_type && r.type==int_type){
else if
else if
else if
else
result.type=int_type;
result.value.i=result.value.i-r.value.i;} (result.type==int_type && r.type==float_type){
result.type=float_type;
result.value.f=result.value.i-r.value.f;} (result.type==float_type && r.type==int_type){
result.type=float_type;
result.value.f=result.value.f-r.value.i;} (result.type==float_type && r.type==float_type){
result.type=float_type; result.value.f=result.value.f-r.value.f;}
(result.type==float_type && r.type==int_type){ result.type=float_type; result.value.f=result.value.f+r.value.i;}
(result.type==float_type && r.type==float_type){ result.type=float_type; result.value.f=result.value.f+r.value.f;}
semantic_error(18,node->line); break;
case N_EXP_LSS : case N_EXP_GTR : case N_EXP_LEQ : case N_EXP_GEQ : case N_EXP_NEQ : case N_EXP_EQL : case N_EXP_AND :


case N_EXP_OR : case N_EXP_ASSIGN :
semantic_error(18,node->line);
break; default :
semantic_error(90,node->line);
break; }
return (result);
}
void semantic_error(int i, int ll, char *s) {
semantic_err++;
printf("*** semantic error at line %d: ",ll); switch (i) {
// errors in expression
case 13:printf("arith type expr required in unary operation\n"); break;
case 18:printf("illegal constant expression \n"); break;
case 19:printf("illegal identifier %s in constant expression\n",s); break;
case 21:printf("illegal type in function call expression\n"); break;
case 24:printf("incompatible type in additive expression\n"); break;
case 27:printf("scalar type expr required in expression\n"); break;
case 28:printf("arith type expression required in binary operation\n"); break;
case 29:printf("integral type expression required in expression\n"); break;
case 31:printf("pointer type expr required in pointer operation\n"); break;


case 32:printf("array type required in array expression\n"); break;
case 34:printf("too many arguments in function call\n"); break;
case 35:printf("too few arguments in function call\n"); break;
case 37:printf("illegal struct field identifier in struct reference expr\n"); break;
case 38:printf("illegal kind of identifier %s in expression\n"); break;
case 39:printf("illegal type size in sizeof operation\n"); break;
case 40:printf("illegal expression type in relational operation"); break;
//case 41:printf("incompatible type in literal\n"); break;
// erros case
case case case case case case case case
in statement
49:printf("scalar type expr required in middle of for-expr\n"); break;
50:printf("integral type expression required in statement\n"); break;
51:printf("illegal expression type in case label\n");
break;
57:printf("not permitted type conversion in return expression\n"); break;
58:printf("not permitted type casting in expression\n");
break;
59:printf("not permitted type conversion in argument\n");
break;
60:printf("expression is not an lvalue \n");
break;
71:printf("case label not within a switch statement \n");
break;
72:printf("default label not within a switch statement \n");


break;
case 73:printf("break statement not within loop or switch stmt\n");
break;
case 74:printf("continue statement not within a loop \n");
break;
// errors in type & declarator
case 80:printf("undefined type\n"); break;
case 81:printf("integer type expression required in enumerator\n"); break;
case 82:printf("illegal array size or type\n"); break;
case 83:printf("illegal element type of array declarator\n"); break;
case 84:printf("illegal type in struct or union field\n"); break;
case 85:printf("invalid function return type\n"); break;
case 86:printf("illegal array size or empty array \n"); break;
case 89:printf("unknown identifier kind: %s\n",s); break;
// misc errors
case 90:printf("fatal compiler error in parse result\n");
break;
case 93:printf("too many literals in source program \n");
break; default:printf("unknown \n");
break; }
}
void semantic_warning(int i, int ll) {
printf("// warning at line %d:",ll);


} }
switch (i) {
case 11:printf("incompatible types in assignment expression\n");
break;
case 12:printf("incompatible types in argument or return expr\n");
break;
case 14:printf("incompatible types in binary expression\n");
break;
case 16:printf("integer type expression is required\n");
break; default:printf("unknown\n");
break;


