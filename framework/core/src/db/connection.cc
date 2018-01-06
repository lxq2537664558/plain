#include "pf/db/query/grammars/grammar.h"
#include "pf/db/interface.h"
#include "pf/db/connection.h"

using namespace pf_basic::type;
using namespace pf_db;

// The construct function.
Connection::Connection(Interface *env, 
                       const std::string &database, 
                       const std::string &table_prefix, 
                       const variable_set_t &config) {
  env_ = env;

  // First we will setup the default properties. We keep track of the DB
  // name we are connected to since it is needed when some reflective 
  // type commands are run such as checking whether a table exists.
  database_ = database;

  table_prefix_ = table_prefix;

  config_ = config;

  // We need to initialize a query grammar and the query post processors 
  // which are both very important parts of the database abstractions 
  // so we initialize these to their default values while starting.
  use_default_query_grammar();
}

// The destruct function.
Connection::~Connection() {

}

// Set the query grammar to the default implementation.
void Connection::use_default_query_grammar() {
  if (!is_null(query_grammar_)) return;
  auto pointer = new query::grammars::Grammar;
  unique_move(query::grammars::Grammar, pointer, query_grammar_);
}

//Run a select statement against the database.
db_fetch_array_t Connection::select(const std::string &query, 
                                    const variable_array_t &bindings) {
  db_fetch_array_t r;
  return run(query, bindings, [this, &r](
        const std::string &query, const variable_array_t &bindings){
    if (pretending()) return r;

    // The query sql string and fetch all result.
    if (!env_->query(query) || !env_->fetch()) return r;

    int32_t columncount = env_->get_columncount();
    if (0 == columncount) return r;

    int32_t i{0};

    // The keys.
    for (i = 0; i < columncount; ++i) { 
      auto columnname = env_->get_columnname(i);
      r.keys.push_back(columnname);
    }

    // The values.
    do {
      for (i = 0; i < columncount; ++i) { 
        variable_t value = env_->get_data(i, "");
        auto columntype = env_->gettype(i);
        if (kDBColumnTypeString == columntype) { 
          value.type = kVariableTypeString;
        } else if (kDBColumnTypeNumber == columntype) { 
          value.type = kVariableTypeNumber;
        } else {
          value.type = kVariableTypeInt64;
        }
        r.values.push_back(value);
      }
    } while (env_->fetch());

    return r;
  });
}

//Begin a fluent query against a database table.
query::Builder Connection::table(const std::string &name) {

}

//Get a new raw query expression.
variable_t Connection::raw(const variable_t &value) {
  return value;
}

//Run a select statement and return a single result.
db_fetch_array_t Connection::select_one(
    const std::string &str, const variable_array_t &bindings) {

}

//Run a select statement against the database.
bool Connection::insert(
    const std::string &str, const variable_array_t &bindings) {

}

//Run an update statement against the database.
int32_t Connection::update(
    const std::string &str, const variable_array_t &bindings) {

}

//Run a delete statement against the database.
int32_t Connection::deleted(
    const std::string &str, const variable_array_t &bindings) {

}

//Execute an SQL statement and return the boolean result.
bool Connection::statement(
    const std::string &str, const variable_array_t &bindings) {

}

//Run an SQL statement and get the number of rows affected.
int32_t Connection::affecting_statement(
    const std::string &str, const variable_array_t &bindings) {

}

//Run a raw, unprepared query against the PDO connection.
bool Connection::unprepared(const std::string &str) {

}

//Prepare the query bindings for execution.
void Connection::prepare_bindings(db_query_bindings_t &bindings) {

}

//Execute a Closure within a transaction.
void Connection::transaction(closure_t callback, int8_t attempts) {

}

//Start a new database transaction.
void Connection::begin_transaction() {

}

//Commit the active database transaction.
void Connection::commit() {

}

//Rollback the active database transaction.
void Connection::rollback() {

}

//Get the number of active transactions.
int32_t Connection::transaction_level() const {

}

//Execute the given callback in "dry run" mode.
void Connection::pretend(closure_t callback) {

}
