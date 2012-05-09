/* 
 * File:   OutputTranslator.cpp
 * Author: Alfred Broda <alfred.broda@gmail.com>
 * 
 * Created on May 7, 2012, 7:57 PM
 */

#include "outputtranslator.hpp"

#include "../mwbase/environment.hpp"

#include "../mwworld/class.hpp"
#include "../mwworld/world.hpp"
#include "../mwworld/player.hpp"

#include <map>

namespace
{

    std::string toLower(const std::string& name)
    {
        std::string lowerCase;

        std::transform(name.begin(), name.end(), std::back_inserter(lowerCase),
                (int(*)(int)) std::tolower);

        return lowerCase;
    }
}

namespace MWWorld
{
    //helper function

    std::string::size_type find_str_ci(const std::string& str, const std::string& substr, size_t pos)
    {
        return toLower(str).find(toLower(substr), pos);
    }

    OutputTranslator::OutputTranslator()
    {
    }

    OutputTranslator::OutputTranslator(const OutputTranslator& orig)
    {
    }

    OutputTranslator::~OutputTranslator()
    {
    }

    /* actual string replacement */
    std::string OutputTranslator::translateOutputText(const MWWorld::Ptr& actor, const std::string& input)
    {
        std::map<std::string, std::string> replaceMap;
        std::string text = input;
        //Replace expressions if present
        if ((find_str_ci(text, (std::string) "%", 0) != std::string::npos)
                || (find_str_ci(text, (std::string) "^", 0) != std::string::npos))
        {
            if (replaceMap.empty())
            {
                //build replacement map for player and NPC
                replaceMap["%pcname"] = std::string(MWWorld::Class::get(MWBase::Environment::get().getWorld()->getPlayer().getPlayer())
                        .getName(MWBase::Environment::get().getWorld()->getPlayer().getPlayer()));
                
                replaceMap["%name"] = std::string(MWWorld::Class::get(actor).getName(actor));
            }

            size_t str_pos;
            for (std::map<std::string, std::string>::iterator ii = replaceMap.begin(); ii != replaceMap.end(); ++ii)
            {

                while ((str_pos = find_str_ci(text, ii->first, 0)) != std::string::npos)
                {
                    try
                    {
                        text.replace(str_pos, ii->first.size(), ii->second);
                    }
                    catch (const std::exception& error)
                    {
                        //printError(std::string("An exception has been thrown: ") + error.what());
                    }
                }

            }
        }
        return text;
    }
};
