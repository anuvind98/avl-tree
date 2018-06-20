rm -f *.svg
dot -Tsvg bst.dot -o bst.svg
xdg-open bst.svg
