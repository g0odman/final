/** Grammars always start with a grammar header. This grammar is called
 *  SPCalculator and must match the filename: SPCalculator.g4
 */
grammar SPCalculator;

/**
* All generated files must reside in the package SP alongside our implementation
* of the tree and the main function.
*/
@header{
package SP;
}

@parser::members{
	//We define a new method in our praser. This method will return a string
	//Representing our tree in LISP-Style
	public String getLisp(){
		StatContext ctx = (StatContext)stat();
		if(ctx.exception!=null){
			return new String("Invalid Expression!");		
		}else{
			return ctx.tree.getLisp();
		}
	}
}

//Valid statement is either a termination command || an arithmetical expression
stat returns [SPTree tree] : e1=TERMINATION {$tree = new SPTree($e1.text);}
			   | e2=exp END {$tree = $e2.tree;}
			   | v=VAR eq=EQ e3=exp
			   		{ $tree = new SPTree($eq.text);
			   		$tree.insertChild(new SPTree($v.text));
			   		$tree.insertChild($e3.tree); }
                           ; 

exp returns [SPTree tree] :
			     OPEN_PAREN exp1=exp CLOSE_PAREN  //parenthesis
					{ $tree = $exp1.tree; }
					
			   | exp1=exp oper=DOLLAR exp2=exp  //dollar operation
			   		{ $tree = new SPTree($oper.text);
			   		$tree.insertChild($exp1.tree);
			   		$tree.insertChild($exp2.tree); }
			   		
			   | exp1=exp oper=MUL_DIV exp2=exp  //multiplication and division
			   		{ $tree = new SPTree($oper.text);
			   		$tree.insertChild($exp1.tree);
			   		$tree.insertChild($exp2.tree); }
			   		
			   | exp1=exp oper=PLUS_MINUS exp2=exp  //addition and subtraction
			   		{ $tree = new SPTree($oper.text);
			   		$tree.insertChild($exp1.tree);
			   		$tree.insertChild($exp2.tree); }
			   		
			   | oper=PLUS_MINUS exp1=exp  //allow extra plus or minus
			   		{ $tree = new SPTree($oper.text);
			   		$tree.insertChild($exp1.tree); }
			   		
			   | mmexp=min_max_exp COMMA exp2=exp CLOSE_PAREN
			   		{ $tree = $mmexp.tree;
			   		$tree.insertChild($exp2.tree); }
			   			
			   | num_val=NUM_OR_VAR  //terminate with number or var
			   		{ $tree = new SPTree($num_val.text); }
			   		
			  ;
min_max_exp returns [SPTree tree] :
			  mmexp=min_max_exp COMMA exp1=exp
			  	{ $tree = $mmexp.tree;
			  	$tree.insertChild($exp1.tree); }
			  | mmoper=MIN_MAX OPEN_PAREN exp1=exp
			  	{ $tree = new SPTree($mmoper.text);
			  	$tree.insertChild($exp1.tree); }
			  ;

// parser rules start with lowercase letters, lexer rules with uppercase
TERMINATION: '<>';
WHITE_SPACE: [ \t\n\r]+ -> skip;
PLUS_MINUS: '+' | '-';
MUL_DIV: '*' | '/';
DOLLAR: '$';
OPEN_PAREN: '(';
CLOSE_PAREN: ')';
COMMA: ',';
END: ';';
EQ: '=';
MIN_MAX: 'max' | 'min';
VAR: [a-z]+;
NUM_OR_VAR: [0-9]+ | [a-z]+; //TODO add caps as well

