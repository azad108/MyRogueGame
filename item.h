#ifndef __ITEM_H__
#define __ITEM_H__

#include <string>
#include <vector>
#include <memory>
class person;
class stats;

class item {
	std::string type;
	int row,col;
 public:
	item(std::string);
	virtual std::string getOutput()=0;
	virtual std::string getSubType()=0;
	virtual void modify(std::shared_ptr<stats>)=0;
	virtual std::string lookAt()=0;
	virtual void setSeen(bool)=0;
	virtual void setMagnitude(float)=0;
	virtual float getMagnitude()=0;
	virtual bool getSeen()=0;
	std::string getType();
	void setPosn(int,int);
	virtual void setGuard(std::shared_ptr<person>);
	virtual std::shared_ptr<person> getGuard();
	int getRow();
	int getCol();
	virtual ~item()=0;
};

#endif
