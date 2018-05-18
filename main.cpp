/* Simple C program that connects to MySQL Database server*/
#include <mysqlpp11/mysqlpp11.h>
#include <string>
#include <iostream>
#include <list>
#include <any>
#include <args.hxx>

using HelpFlagType = args::HelpFlag;
using VerboseArgType = args::Flag;
using ServernameArgType = args::ValueFlag<std::string>;
using UsernameArgType = args::ValueFlag<std::string>;
using PasswordArgType = args::ValueFlag<std::string>;
using DatabaseArgType = args::ValueFlag<std::string>;

using ListOfAnything = std::list<std::any>;

template<typename T>
T get_any(std::any& anything)
{
      return std::any_cast<T>(anything);
}

namespace mysqlpp = daotk::mysql;

/**
 * \mainpage
 
 * @brief 
 * 
 * @param argc number of arguments (supplied automatically by the operating system)
 * @param argv vector of strings to be interpreted as arguments (supplied by O/S)
 * @return int error code:
 * 
 * exit error codes
 * <ol>
 * <li>0 no error</li>
 * <li>-1 completion error (command line parsing error)</li>
 * <li>-2 parsing error (command line parsing error)</li>
 * <li>-3 unable to connect to database</li>
 * </ol>
 *                                                                              
 */

int main(int argc, char** argv) 
{
      /* create the parser */
      args::ArgumentParser parser("Example MySQL program.",
                                  "Copyright 2018 Real-Time Innovations, Inc.");

      /* add flags to the parser */
      HelpFlagType         help(parser, "HELP", "Display this help menu", {'h', "help"});
      VerboseArgType       verbose(parser, "verbose", "output progess messages", {"v", "verbose"});
      ServernameArgType    servername(parser, "server", "server hostname / ip", {"s", "servername"}, "localhost");
      UsernameArgType      username(parser, "username", "username", {"u", "username"}, "root");
      PasswordArgType      password(parser, "password", "password", {"p", "password"});
      DatabaseArgType      database(parser, "database", "Database name", {"d", "database"});

      /* complete parsing definition */
      args::CompletionFlag completion(parser, {"complete"});

      try {
            /* parse what is available in argv */
            parser.ParseCLI(argc, argv);
      } catch (args::Completion e) {
            std::cout << e.what();
            return -1;
      } catch (args::Help) {
            std::cout << parser;
            return 0;
      } catch (args::ParseError e) {
            std::cerr << e.what() << std::endl;
            std::cerr << parser;
            return -2;
      }

      /* connect to the database */
      mysqlpp::connection con(servername.Get(), 
                              username.Get(), 
                              password.Get(), 
                              database.Get());

      if(!con) {
            exit(-3);
      }

      /* retrieve tables in the database */
      ListOfAnything tables;
      auto tab = con.query("show tables");
      for(auto table: tab.as_container<std::string>()) {
            auto [name] = table;
            tables.emplace_back(name);
      }

      /* for each table, do a "select * from" */
      for(auto table: tables) {
            std::string term("select * from ");
            term += get_any<std::string>(table);

            std::cout << "Issuing SQL command: [" << term << "]:\n";
            auto res = con.query(term);
            for(auto row: res.as_container<int, std::string>()) {
                  auto [id, name] = row;
                  std::cout << "id = " << id << " name " << name << '\n';
            }
      }

      exit(0);
}
