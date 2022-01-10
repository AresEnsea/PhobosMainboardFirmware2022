documentation:
	'/Applications/Doxygen.app/Contents/Resources/doxygen' doxyconfig
	rm -r ./docs/
	cp -R Doxygen/html/ docs/