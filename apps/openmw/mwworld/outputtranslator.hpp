/* 
 * File:   OutputTranslator.hpp
 * Author: Alfred Broda <alfred.broda@gmail.com>
 *
 * Created on May 7, 2012, 7:57 PM
 */

#ifndef OUTPUTTRANSLATOR_HPP
#define	OUTPUTTRANSLATOR_HPP

#include <string>

#include "../mwworld/ptr.hpp"

namespace MWWorld {

    class OutputTranslator {
    public:
        OutputTranslator();
        OutputTranslator(const OutputTranslator& orig);
        virtual ~OutputTranslator();

        //string replacement
        static std::string translateOutputText(const MWWorld::Ptr& actor, const std::string& input);

    private:

    };
}
#endif	/* OUTPUTTRANSLATOR_HPP */

