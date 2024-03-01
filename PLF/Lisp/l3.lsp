; 6
; Write a function that returns the maximum of numeric atoms in a list, at any level
; (Solve the following problems using MAP functions)

(defun getmax (l)
	(cond
		((listp l) (apply 'max (mapcar 'getmax l)))
        ((numberp l) l)
        (t MOST-NEGATIVE-DOUBLE-FLOAT) ; (t 0)
	)
)
(print (getmax '(1 2 B 3 (-1 A (100))) ))
