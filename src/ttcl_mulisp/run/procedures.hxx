#ifndef TTCL_MULISP_RUN_PROCEDURES_HXX
#define TTCL_MULISP_RUN_PROCEDURES_HXX

// TTCL: The Template Clustering Library

/** @file
    Lisp interpreter - Lisp interpreter
    @author Edgar Gonzàlez i Pellicer
*/

#include <ttcl_mulisp/sexp/sexp_native.hxx>

/// TTCL µLisp Namespace
namespace ttcl_mulisp {

  // Interpreter Namespace
  namespace run {

    /// (and expr...)
    sexp::sexp_ptr
    and_procedure(const std::vector<sexp::sexp_ptr>& _args,
                  interpreter& _interpreter);

    /// (append expr...)
    sexp::sexp_ptr
    append_procedure(const std::vector<sexp::sexp_ptr>& _args,
                     interpreter& _interpreter);

    /// (apply expr expr)
    sexp::sexp_ptr
    apply_procedure(const std::vector<sexp::sexp_ptr>& _args,
                    interpreter& _interpreter);

    /// (begin expr...)
    sexp::sexp_ptr
    begin_procedure(const std::vector<sexp::sexp_ptr>& _args,
                    interpreter& _interpreter);

    /// (car expr)
    sexp::sexp_ptr
    car_procedure(const std::vector<sexp::sexp_ptr>& _args,
                  interpreter& _interpreter);

    /// (cdr expr)
    sexp::sexp_ptr
    cdr_procedure(const std::vector<sexp::sexp_ptr>& _args,
                  interpreter& _interpreter);

    /// (cond (expr expr...) ...)
    sexp::sexp_ptr
    cond_procedure(const std::vector<sexp::sexp_ptr>& _args,
                   interpreter& _interpreter);

    /// (cons expr expr)
    sexp::sexp_ptr
    cons_procedure(const std::vector<sexp::sexp_ptr>& _args,
                   interpreter& _interpreter);

    /// (copying)
    sexp::sexp_ptr
    copying_procedure(const std::vector<sexp::sexp_ptr>& _args,
                      interpreter& _interpreter);

    /// (define (symbol...) expr...)
    sexp::sexp_ptr
    define_procedure(const std::vector<sexp::sexp_ptr>& _args,
                     interpreter& _interpreter);

    /// (display expr)
    sexp::sexp_ptr
    display_procedure(const std::vector<sexp::sexp_ptr>& _args,
                      interpreter& _interpreter);

    /// (error expr...)
    sexp::sexp_ptr
    error_procedure(const std::vector<sexp::sexp_ptr>& _args,
                    interpreter& _interpreter);

    /// (eval expr)
    sexp::sexp_ptr
    eval_procedure(const std::vector<sexp::sexp_ptr>& _args,
                   interpreter& _interpreter);

    /// (foreach symbol expr expr...)
    sexp::sexp_ptr
    foreach_procedure(const std::vector<sexp::sexp_ptr>& _args,
                      interpreter& _interpreter);

    /// (if expr expr [expr])
    sexp::sexp_ptr
    if_procedure(const std::vector<sexp::sexp_ptr>& _args,
                 interpreter& _interpreter);

    /// (lambda (symbol...) expr...)
    sexp::sexp_ptr
    lambda_procedure(const std::vector<sexp::sexp_ptr>& _args,
                     interpreter& _interpreter);

    /// (let* ((symbol expr) ...) expr ...)
    sexp::sexp_ptr
    let_star_procedure(const std::vector<sexp::sexp_ptr>& _args,
                       interpreter& _interpreter);

    /// (list expr ...)
    sexp::sexp_ptr
    list_procedure(const std::vector<sexp::sexp_ptr>& _args,
                   interpreter& _interpreter);

    /// (map expr)
    sexp::sexp_ptr
    map_procedure(const std::vector<sexp::sexp_ptr>& _args,
                  interpreter& _interpreter);

    /// (not expr)
    sexp::sexp_ptr
    not_procedure(const std::vector<sexp::sexp_ptr>& _args,
                  interpreter& _interpreter);

    /// (null? expr)
    sexp::sexp_ptr
    nullp_procedure(const std::vector<sexp::sexp_ptr>& _args,
                    interpreter& _interpreter);

    /// (newline)
    sexp::sexp_ptr
    newline_procedure(const std::vector<sexp::sexp_ptr>& _args,
                      interpreter& _interpreter);

    /// (/ expr...)
    sexp::sexp_ptr
    number_divides_procedure(const std::vector<sexp::sexp_ptr>& _args,
                             interpreter& _interpreter);

    /// (= expr...)
    sexp::sexp_ptr
    number_equal_to_procedure(const std::vector<sexp::sexp_ptr>& _args,
                              interpreter& _interpreter);

    /// (> expr...)
    sexp::sexp_ptr
    number_greater_procedure(const std::vector<sexp::sexp_ptr>& _args,
                             interpreter& _interpreter);

    /// (>= expr...)
    sexp::sexp_ptr
    number_greater_equal_procedure(const std::vector<sexp::sexp_ptr>& _args,
                                   interpreter& _interpreter);

    /// (< expr ...)
    sexp::sexp_ptr
    number_less_procedure(const std::vector<sexp::sexp_ptr>& _args,
                          interpreter& _interpreter);

    /// (<= expr...)
    sexp::sexp_ptr
    number_less_equal_procedure(const std::vector<sexp::sexp_ptr>& _args,
                                interpreter& _interpreter);

    /// (- expr ...)
    sexp::sexp_ptr
    number_minus_procedure(const std::vector<sexp::sexp_ptr>& _args,
                           interpreter& _interpreter);

    /// (* expr ...)
    sexp::sexp_ptr
    number_multiplies_procedure(const std::vector<sexp::sexp_ptr>& _args,
                                interpreter& _interpreter);

    /// (+ expr ...)
    sexp::sexp_ptr
    number_plus_procedure(const std::vector<sexp::sexp_ptr>& _args,
                          interpreter& _interpreter);

    /// (or expr ...)
    sexp::sexp_ptr
    or_procedure(const std::vector<sexp::sexp_ptr>& _args,
                 interpreter& _interpreter);

    /// (parse expr ...)
    sexp::sexp_ptr
    parse_procedure(const std::vector<sexp::sexp_ptr>& _args,
                    interpreter& _interpreter);

    /// `expr
    sexp::sexp_ptr
    quasiquote_procedure(const std::vector<sexp::sexp_ptr>& _args,
                         interpreter& _interpreter);

    /// 'expr
    sexp::sexp_ptr
    quote_procedure(const std::vector<sexp::sexp_ptr>& _args,
                    interpreter& _interpreter);

    /// (reverse expr)
    sexp::sexp_ptr
    reverse_procedure(const std::vector<sexp::sexp_ptr>& _args,
                      interpreter& _interpreter);

    /// (set symbol expr)
    sexp::sexp_ptr
    set_procedure(const std::vector<sexp::sexp_ptr>& _args,
                  interpreter& _interpreter);

    /// (string-append expr ...)
    sexp::sexp_ptr
    string_append_procedure(const std::vector<sexp::sexp_ptr>& _args,
                            interpreter& _interpreter);

    /// (string= expr ...)
    sexp::sexp_ptr
    string_equal_to_procedure(const std::vector<sexp::sexp_ptr>& _args,
                              interpreter& _interpreter);

    /// (string> expr ...)
    sexp::sexp_ptr
    string_greater_procedure(const std::vector<sexp::sexp_ptr>& _args,
                             interpreter& _interpreter);

    /// (string>= expr ...)
    sexp::sexp_ptr
    string_greater_equal_procedure(const std::vector<sexp::sexp_ptr>& _args,
                                   interpreter& _interpreter);

    /// (string<= expr ...)
    sexp::sexp_ptr
    string_less_equal_procedure(const std::vector<sexp::sexp_ptr>& _args,
                                interpreter& _interpreter);

    /// (string< expr ...)
    sexp::sexp_ptr
    string_less_procedure(const std::vector<sexp::sexp_ptr>& _args,
                          interpreter& _interpreter);

    /// (warranty)
    sexp::sexp_ptr
    warranty_procedure(const std::vector<sexp::sexp_ptr>& _args,
                       interpreter& _interpreter);

    /// (write expr)
    sexp::sexp_ptr
    write_procedure(const std::vector<sexp::sexp_ptr>& _args,
                    interpreter& _interpreter);

    /// (while expr)
    sexp::sexp_ptr
    while_procedure(const std::vector<sexp::sexp_ptr>& _args,
                    interpreter& _interpreter);
  }
}

#endif

// Local Variables:
// coding: utf-8
// End:
