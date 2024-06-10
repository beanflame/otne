// otne_parse hello ~


#pragma once

#include "otne_lexer.hpp"

namespace otne
{
    class Parser
    {
        private:
            std::vector<token> token_list;
            
        public:
            Parser();
            ~Parser();

            // Parse token_list
            Parser(std::vector<token> tl);
    };
};