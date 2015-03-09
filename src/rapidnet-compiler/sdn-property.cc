/*
 * property.cc
 *
 *  Created on: Mar 5, 2015
 *      Author: chen
 */

#include "sdn-property.h"

NS_LOG_COMPONENT_DEFINE ("Property");

Property::Property()
{
	map<string, Variable*> varMap;

	uniVars = list<Variable*>();
	univPredList = list<PredicateInstance*>();
	univConsList = new ConstraintsTemplate();
	existVars = list<Variable*>();
	existPredList = list<PredicateInstance*>();
	existConsList = new ConstraintsTemplate();

	ProcessUniPred("bestRoute(a,b,c)", varMap);

	ProcessUniPred("verifyPath(m,n,l)", varMap);
	NS_LOG_DEBUG("Reach here?!");
	ProcessUniCons(varMap);

	ProcessExistPred("line(o,p)", varMap);
	ProcessExistPred("link(r,s,t)", varMap);
	ProcessExistCons(varMap);
}

//TODO: Parse constraints from user input
void
Property::ProcessUniCons(const map<string, Variable*>& varMap)
{
	/*Constraint template*/
//	string var1 = "a";
//	Variable* varPtr = varMap.find(var1)->second;
//
//	Constraint* newCons = new Constraint(Constraint::LT, varPtr, new IntVal(4));
//
//	univConsList->AddConstraint(newCons);
//	NS_LOG_DEBUG("Reach here?!");
}

void
Property::ProcessExistCons(const map<string, Variable*>& varMap)
{
	/*Constraint template*/

//	string var1 = "r";
//	map<string, Variable*>::const_iterator itm = varMap.find(var1);
//	if (itm == varMap.end())
//	{
//		NS_LOG_ERROR("Variable " << var1 << "not found!");
//		return;
//	}
//	Variable* varPtr1 = itm->second;
//
//	string var2 = "b";
//	itm = varMap.find(var2);
//	if (itm == varMap.end())
//	{
//		NS_LOG_ERROR("Variable " << var1 << "not found!");
//		return;
//	}
//	Variable* varPtr2 = itm->second;
//	Constraint* newCons = new Constraint(Constraint::EQ, varPtr1, varPtr2);
//	existConsList->AddConstraint(newCons);
}


vector<Term*>
Property::ParseArgs(const string args, map<string, Variable*>& varMap)
{
	//Example args: "v1,v2,v3...,vn"
	vector<Term*> vlist;
	istringstream ss(args);
	string arg;
	Variable* newVar = NULL;
	while (getline(ss, arg, ','))
	{
		//TODO: Replace default type
		NS_LOG_DEBUG("Process variable: " << arg);
		newVar = new Variable(Variable::STRING, true);
		vlist.push_back(newVar);
		varMap.insert(map<string,Variable*>::value_type(arg, newVar));
	}

	return vlist;
}

void
Property::ProcessUniPred(string line, map<string, Variable*>& varMap)
{
	PredicateInstance* predInst = ParsePred(line, varMap);
	univPredList.push_back(predInst);
}

void
Property::ProcessExistPred(const string line, map<string, Variable*>& varMap)
{
	PredicateInstance* predInst = ParsePred(line, varMap);
	existPredList.push_back(predInst);
}

PredicateInstance*
Property::ParsePred(const string line, map<string, Variable*>& varMap)
{
	size_t leftParPos = line.find("(");
	string predName = line.substr(0, leftParPos+1);
	size_t rightParPos = line.find(")");
	string predArgs = line.substr(leftParPos+1, (rightParPos - leftParPos - 1));
	vector<Term*> args = ParseArgs(predArgs, varMap);
	int arg_length = args.size();
	vector<Variable::TypeCode> typeVec = vector<Variable::TypeCode>(arg_length, Variable::STRING);
	PredicateSchema* schema = new PredicateSchema(predName, typeVec);
	return (new PredicateInstance(schema, args));
}


void
Property::Print() const
{
	cout << endl;
	cout << "********** User-defined Property ***********" << endl;

	//Print universally quantified variables
	cout << "forall ";
	list<Variable*>::const_iterator itv;
	for (itv = uniVars.begin();itv != uniVars.end();itv++)
	{
		(*itv)->PrintTerm();
		cout << ",";
	}

	NS_LOG_DEBUG("Reach here!!!");

	list<PredicateInstance*>::const_iterator itp;
	for (itp = univPredList.begin();itp != univPredList.end();itp++)
	{
		const vector<Term*>& varVec = (*itp)->GetArgs();
		vector<Term*>::const_iterator itt;
		for (itt = varVec.begin();itt != varVec.end();itt++)
		{
			(*itt)->PrintTerm();
			cout << ",";
		}
	}



	cout << endl;

	//Print universally quantified predicates
	for (itp = univPredList.begin();itp != univPredList.end();itp++)
	{
		(*itp)->Print();
		cout << " /\\ " << endl;
	}

	//Print universally quantified constraints
	univConsList->PrintTemplate();

	cout << endl << "->";

	//Print existentially quantified variables
	cout << "exists ";
	for (itv = existVars.begin();itv != existVars.end();itv++)
	{
		(*itv)->PrintTerm();
		cout << ",";
	}
	for (itp = existPredList.begin();itp != existPredList.end();itp++)
	{
		const vector<Term*>& varVec = (*itp)->GetArgs();
		vector<Term*>::const_iterator itt;
		for (itt = varVec.begin();itt != varVec.end();itt++)
		{
			(*itt)->PrintTerm();
			cout << ",";
		}
	}

	cout << endl;

	//Print existentially quantified predicates
	for (itp = existPredList.begin();itp != existPredList.end();itp++)
	{
		(*itp)->Print();
		cout << " /\\ " << endl;
	}

	existConsList->PrintTemplate();

	cout << "*********************";
	cout << endl;
}

Property::~Property()
{
	delete univConsList;
	delete existConsList;

	list<Variable*>::iterator itv;
	for (itv = uniVars.begin();itv != uniVars.end();itv++)
	{
		delete (*itv);
	}
	for (itv = existVars.begin();itv != existVars.end();itv++)
	{
		delete (*itv);
	}

	list<PredicateInstance*>::iterator itl;
	for (itl = univPredList.begin();itl != univPredList.end();itl++)
	{
		delete (*itl);
	}

	for (itl = existPredList.begin();itl != existPredList.end();itl++)
	{
		delete (*itl);
	}
}
