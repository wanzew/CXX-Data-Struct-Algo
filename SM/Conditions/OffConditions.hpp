#ifndef OFFCONDITION_HPP
#define OFFCONDITION_HPP

#include <iostream>
#include "../include/SuppressionList.hpp"
#include "../include/debouncerSuppressionBool.hpp"
#include "SuppressionReasons.hpp"
#include "../include/enum.hpp"

class OffConditions {

public:
	OffConditions()
		: m_suppressionContainer()
		, m_suppressionYawrate()
	{
		m_suppressionContainer.add(m_suppressionYawrate);
	}

	void calculateCondition(
		const Fip*		fip
	);

	bool getConditions() const {
		return m_suppressionContainer.isSuppressed();
	}

private:
	SuppressionList			m_suppressionContainer;
	SuppYawrate*			m_suppressionYawrate;

};



#endif // !PASSIVECONDITION_HPP
