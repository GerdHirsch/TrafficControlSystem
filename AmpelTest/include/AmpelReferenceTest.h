/*
 * AmpelReferenceTest.h
 *
 *  Created on: 26.11.2017
 *      Author: Gerd
 */

#ifndef INCLUDE_AMPELREFERENCETEST_H_
#define INCLUDE_AMPELREFERENCETEST_H_

#include "AmpelTest.h"
#include "AmpelReference.h"

class AmpelReferenceTest : public AmpelTest
{
public:
	using this_type = AmpelReferenceTest;
	using base_type = AmpelTest;

	AmpelReferenceTest() : referenceImplementation(red, yellow, green)
{}
	static cute::suite make_suite(){
		return base_type::make_suite<this_type>();
	}
protected:
	SUT& createSUT() {
		return referenceImplementation;
	}

	void initBlinkend_aus() { red.off(); yellow.off(); green.on();	}
private:
	AmpelReference referenceImplementation;
};



#endif /* INCLUDE_AMPELREFERENCETEST_H_ */
