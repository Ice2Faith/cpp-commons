#ifndef _I2F_IEQUALS_H_
#define _I2F_IEQUALS_H_


class IEquals
{
public:
	virtual ~IEquals(){}
	virtual bool equals(const IEquals& val) =0;
};

#endif // _I2F_IEQUALS_H_