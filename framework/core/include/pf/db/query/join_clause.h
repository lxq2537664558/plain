/**
 * PLAIN FRAMEWORK ( https://github.com/viticm/plainframework )
 * $Id join_clause.h
 * @link https://github.com/viticm/plainframework for the canonical source repository
 * @copyright Copyright (c) 2014- viticm( viticm.ti@gmail.com )
 * @license
 * @user viticm<viticm.ti@gmail.com>
 * @date 2017/12/14 16:32
 * @uses your description
*/
#ifndef PF_DB_QUERY_JOIN_CLAUSE_H_
#define PF_DB_QUERY_JOIN_CLAUSE_H_

#include "pf/db/query/config.h"
#include "pf/db/query/builder.h"

namespace pf_db {

namespace query {

class PF_API JoinClause : public Builder {

  public:
    JoinClause(Builder *parent_query, 
               const std::string &type, 
               const std::string &table) 
      : Builder(parent_query->get_connection(), parent_query->get_grammar()),
        type_{type},
        table_{table},
        parent_query_{parent_query} { class_name_ = "JoinClause"; }

    virtual ~JoinClause() {};

 public:

    //The type of join being performed.
    std::string type_;

    //The table the join clause is joining to.
    std::string table_;

 public:

    //Add an "on" clause to the join.
    JoinClause &on(const std::string &first, 
                   const std::string &oper = "", 
                   const std::string &second = "", 
                   const std::string &boolean = "and");

    //Add an "or on" clause to the join.
    JoinClause &or_on(const std::string &first,
                      const std::string &oper = "",
                      const std::string &second = "");

    //Get a new instance of the join clause builder.
    JoinClause *new_query() {
       return new JoinClause(parent_query_, type_, table_);
    }

 private:

    //The parent query builder instance.
    Builder *parent_query_;

};

}; //namespace query

}; //namespace pf_db


#endif //PF_DB_QUERY_JOIN_CLAUSE_H_
