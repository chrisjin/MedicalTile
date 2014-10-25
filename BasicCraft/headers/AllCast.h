#pragma once
template<class InputType,class OutPutType>
union cast_union
{
	InputType in;
	OutPutType out;
};
template <class InputType, class OutPutType>
OutPutType All_cast(InputType a)
{
	cast_union<InputType,OutPutType> u;
	u.in=a;
	return u.out;
}