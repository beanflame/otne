// otne_parse hello ~


#pragma once

#include "otne_lexer.hpp"

namespace otne
{
    class Parse
    {
        private:
            std::vector<token> token_list;
            
        public:
            Parse();
            ~Parse();

            // Parse token_list
            Parse(std::vector<token> tl);
    };
};