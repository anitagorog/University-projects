; 6.

; a) Write a function to test whether a list is linear.

(defun linearList (l)
    (cond
        ((null l) T)
        ((listp (car l)) nil)
        (T (linearList (cdr l)))
    )
)

(print (linearList '(a (b c) (d (e (f))))))
;=> nil

(print (linearList '(1 2 3 4)))
;=> T



; b) Write a function to replace the first occurence of an element E in a given list with an other element O.

(defun replaceFirstElement (l e o)
    (cond
        ((null l) nil)
        ((= (car l) e) (cons o (cdr l)))
        (T (cons (car l) (replaceFirstElement (cdr l) e o)))
    )
)

(print (replaceFirstElement '(1 2 3 4 5 6 7 6 4 6) 6 0))
;=> (1 2 3 4 5 0 7 6 4 6) 



; c) Write a function to replace each sublist of a list with its last element.
;  A sublist is an element from the first level, which is a list.
;  Example: (a (b c) (d (e (f)))) ==> (a c (e (f))) ==> (a c (f)) ==> (a c f)
;  (a (b c) (d ((e) f))) ==> (a c ((e) f)) ==> (a c f)

(defun last_element (l)
	(if (listp l) 
        (last_element (car (reverse l)))
        l
    )
)

(print (last_element '(1 2 (3 (4 5)))))
; => 5

(defun replaceWithLastElement (l)
	(cond
		((null l) nil)
		((listp (car l)) (cons (last_element (car l)) (replaceWithLastElement (cdr l))))
		(T (cons (car l) (replaceWithLastElement (cdr l))))
	)
)

(print (replaceWithLastElement '(a (b c) (d (e (f))))))
; => '(a c f)


; d) Write a function to merge two sorted lists without keeping double values

(defun merge_sorted (a b)
	(cond
		((null a) b)
		((null b) a)
		((<= (car a) (car b)) (cons (car a) (merge_sorted (cdr a) b)))
		(T (cons (car b) (merge_sorted a (cdr b))))
	)
)

(print (merge_sorted '(1 2 3 3) '(3 4 4 5 5 7)))
; => (1 2 3 3 3 4 4 5 5 7)


(defun remove_doubles (l)
    (cond
        ;((null l) nil)
        ((null (cdr l)) l) ; null not a number - if this not put
            ; here already returns a LIST
        ((= (car l) (cadr l)) (remove_doubles (cdr l)))
        (T (cons (car l) (remove_doubles (cdr l))))
    )
)

(print (remove_doubles '(1 2 3 3 4 4 5 7 7)))
;=> (1 2 3 4 5 7) 

(defun solve (a b)
    (remove_doubles (merge_sorted a b))
)

(print (solve '(1 2 3 3 8) '(3 4 4 5 5 7)))
;=> (1 2 3 4 5 7 8) 