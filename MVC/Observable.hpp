#pragma once

#include <list>
#include "Observateur.hpp"

template<typename T>
class Observable {
private:
	std::list<Observateur<T> *> list_observateurs;

public:
	/*
	But: notifie tous les observateurs
	Antecedent: info de type T
	*/
	void notifierObservateurs(T info){
		for (auto obs : this->list_observateurs){
			obs->update(info);
		}
	}
	/*
	But: ajoute un observateur
	Antecedent: pointeur sur obersateur de type T
	Consequent: le pointeur est ajouter au vecteur list_observateurs
	*/
	void ajouterObservateur(Observateur<T> * observateur){
		this->list_observateurs.push_back(observateur);
	}
};