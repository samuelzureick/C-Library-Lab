#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <cmath>
#include "library.h"


/* Document definitions */
void Document::updateTitle(const char *newTitle) {
	_title = (char *)malloc(sizeof(char) *strlen(newTitle));
	_title = (char *)newTitle;
}

void Document::updateYear(int newYear) {
	_year = newYear;
}

void Document::updateQuantity(int newQuantity) {
	_quantity = newQuantity;
}

char *Document::getTitle() {
	return _title;
}

int Document::getYear() {
	return _year;
}

int Document::getQuantity() {
	return _quantity;
}

int Document::borrowDoc() {
	if (_quantity > 0) {
		_quantity = _quantity - 1;
		return 0;
	}
	return 1;
}

void Document::returnDoc() {
	_quantity = _quantity + 1;
}



/* Novel Definitions */

Novel::Novel(const char *title, const char *author, int year, int quantity) {
	_title = (char *)malloc(sizeof(char) *strlen(title));
	_title = (char *)title;
	_author = (char *)malloc(sizeof(char) *strlen(author));
	_author = (char *)author;
	_year = year;
	_quantity = quantity;
}

Novel::~Novel() {
	printf("destructor called\n");
}

document_type Novel::getDocType() {
	return DOC_NOVEL;
}

void Novel::print() {
	printf("Novel, title: ");

	for(int i = 0; i < strlen(_title); i++) {
		printf("%c",_title[i]);
	}
	printf(", author: ");

	for(int i = 0; i < strlen(_author); i++) {
		printf("%c",_author[i]);
	}
	printf(", year: %d, quantity: %d\n", _year, _quantity);
}

void Novel::updateAuthor(const char *newAuthor) {
	*_author = *newAuthor;
}

char *Novel::getAuthor() {
	return _author;
}



/* Comic Definitions */

Comic::Comic(const char *title, const char *author, int issue, int year, int quantity) {
	_title = (char *)malloc(sizeof(char) *strlen(title));
	_title = (char *)title;
	_author = (char *)malloc(sizeof(char) *strlen(author));
	_author = (char *)author;
	_issue = issue;
	_year = year;
	_quantity = quantity;
}

Comic::~Comic() {
	printf("destructor called\n");
}

document_type Comic::getDocType() {
	return DOC_COMIC;
}

void Comic::print() {
	printf("Comic, title: ");

	for(int i = 0; i < strlen(_title); i++) {
		printf("%c",_title[i]);
	}
	printf(", author: ");

	for(int i = 0; i < strlen(_author); i++) {
		printf("%c",_author[i]);
	}
	printf(", issue: %d, year: %d, quantity: %d\n", _issue, _year, _quantity);
}

void Comic::updateAuthor(const char *newAuthor) {
	*_author = *newAuthor;
}

void Comic::updateIssue(int newIssue) {
	_issue = newIssue;
}

char *Comic::getAuthor() {
	return _author;
}

int Comic::getIssue() {
	return _issue;
}



/* Magazine Definitions*/

Magazine::Magazine(const char *title, int issue, int year, int quantity) {
	_title = (char *)malloc(sizeof(char) *strlen(title));
	_title = (char *)title;
	
	_issue = issue;
	_year = year;
	_quantity = quantity;
}

Magazine::~Magazine() {
	printf("destructor called\n");
}

document_type Magazine::getDocType() {
	return DOC_MAGAZINE;
}

void Magazine::print() {
	printf("Magazine, title: ");

	for(int i = 0; i < strlen(_title); i++) {
		printf("%c",_title[i]);
	}
	printf(", issue: %d, year: %d, quantity: %d\n", _issue, _year, _quantity);
	
}

void Magazine::updateIssue(int newIssue) {
	_issue = newIssue;
}

int Magazine::getIssue() {
	return _issue;
}


/* Library Implementation */

Library::Library() {
}

void Library::print() {
	for (int i = 0; i < _docs.size(); i++) {
		_docs.at(i)->print();
	}
}

int Library::dumpCSV(const char *filename) {
	int fileref = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fileref == -1) {
		printf("error with open\n");
		return -1;
	}

	for (int i = 0; i < _docs.size(); i++) {
		if (_docs.at(i)->getDocType() == DOC_NOVEL) {
			char writebuffer[128];
			sprintf(writebuffer, "novel,%s,%s,,%d,%d\n",((Novel *)_docs.at(i))->getTitle(),((Novel *)_docs.at(i))->getAuthor(),((Novel *)_docs.at(i))->getYear(),((Novel *)_docs.at(i))->getQuantity());
			if(write(fileref, writebuffer,strlen(writebuffer)) != strlen(writebuffer)) {
				printf("error writing\n");
				close(fileref); return -1;
			}
		}
		else if (_docs.at(i)->getDocType() == DOC_COMIC) {
			char writebuffer[128];
			sprintf(writebuffer, "comic,%s,%s,%d,%d,%d\n",((Comic *)_docs.at(i))->getTitle(),((Comic *)_docs.at(i))->getAuthor(),((Comic *)_docs.at(i))->getIssue(),((Comic *)_docs.at(i))->getYear(),((Comic *)_docs.at(i))->getQuantity());
			if(write(fileref, writebuffer,strlen(writebuffer)) != strlen(writebuffer)) {
				printf("error writing\n");
				close(fileref); return -1;
			}
		}
		else {
			char writebuffer[128];
			sprintf(writebuffer, "magazine,%s,%d,%d,%d\n",((Magazine *)_docs.at(i))->getTitle(),((Magazine *)_docs.at(i))->getIssue(),((Magazine *)_docs.at(i))->getYear(),((Magazine *)_docs.at(i))->getQuantity());
			if(write(fileref, writebuffer,strlen(writebuffer)) != strlen(writebuffer)) {
				printf("error writing\n");
				close(fileref); return -1;
			}
		}

	}
	return 0;
}

Document *Library::searchDocument(const char *title) {
	for (int i = 0; i <_docs.size(); i++) {
		if (title == _docs.at(i)->getTitle()) {
			return _docs.at(i);
		}
	}
	return NULL;
}

int Library::addDocument(Document *d) {
	for (int i = 0; i < _docs.size(); i++) {
		if (d->getTitle() == _docs.at(i)->getTitle()){
			return 1;
		}
	}

	_docs.push_back(d);
	return 0;
}

int Library::delDocument(const char *title) {
	for (int i = 0; i < _docs.size(); i++) {
		if (title ==_docs.at(i)->getTitle()){
			_docs.erase(_docs.begin()+i);
			return 0;
		}
	}
	return 1;
}

int Library::countDocumentOfType(document_type t) {
	int count = 0;
	for (int i = 0; i < _docs.size(); i++) {
		if (_docs.at(i)->getDocType()==t) {
			count ++;
		}
	}
	return count;
}

int Library::borrowDoc(const char *title) {
	if (searchDocument(title) != NULL) {
		if (searchDocument(title)->borrowDoc() == 0) {
			return 0;
		}
	}
	return 1;
}
int Library::returnDoc(const char *title) {
	if (searchDocument(title) != NULL) {
		searchDocument(title)->returnDoc();
		return 0;
	}
	return 1;
}

