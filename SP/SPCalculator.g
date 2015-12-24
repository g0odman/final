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
			   | e2=exp {$tree = $e2.tree;}
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
			   		
			   | num=NUMBER  //terminate with number
			   		{ $tree = new SPTree($num.text); }
			   		
			   | oper=PLUS_MINUS exp1=exp  //allow extra plus or minus
			   		{ $tree = new SPTree($oper.text);
			   		SPTree zeroTree = new SPTree("0");
			   		$tree.insertChild(zeroTree);
			   		$tree.insertChild($exp1.tree); }
			   		
			  ;

// parser rules start with lowercase letters, lexer rules with uppercase
TERMINATION: '<>';
NUMBER: [0-9]+;
WHITE_SPACE: [ \t\n\r]+ -> skip;
PLUS_MINUS: '+' | '-';
MUL_DIV: '*' | '/';
DOLLAR: '$';
OPEN_PAREN: '(';
CLOSE_PAREN: ')';
