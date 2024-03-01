; 6
; Return the list of nodes of a tree of type (1) accessed inorder.

(defun parcurg_st(arb nv nm)
    (cond
    ( (null arb) nil)
    ( (= nv (+ 1 nm)) nil )
    ( t (cons (car arb) 
        (cons (cadr arb)
            (parcurg_st (cddr arb) (+ 1 nv) (+ (cadr arb) nm))
        )
        )
    )
    )
)
;nv – number of vertices
;nm – number of edges

(defun stang (arb)
    (parcurg_st (cddr arb) 0 0)
)

; functions parcurg_st and stang are from the lecture

(defun myinorder (l)
    (cond 
        ( (null l) nil )
        ( (null (stang l)) (list(car l)) )
        ( T ( append (myinorder(stang l)) (list(car l)) 
              (myinorder(nthcdr (+ 2 (length (stang l))) l)) ) )
    )
)

(print '(a 2 b 2 c 1 i 0 f 1 g 0 d 2 e 0 h 0))
(print "The inorder")
(print (myinorder '(a 2 b 2 c 1 i 0 f 1 g 0 d 2 e 0 h 0)) )

(print "Other example")
(print '(A 2 B 0 C 2 D 0 E 0))
(print "The inorder")
(print (myinorder '(A 2 B 0 C 2 D 0 E 0)) )
