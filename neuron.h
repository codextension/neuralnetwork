//
// Created by elie on 12.03.18.
//

#ifndef NEURALNETWORK_NEURON_H
#define NEURALNETWORK_NEURON_H

#include <string>
#include <iostream>
#include <vector>
#include "utilities.h"
#include <list>
#include <map>
#include <sstream>

using namespace std;

namespace cx {

    class synapse;

    class neuron {
    protected:
        double value = 0;
        string id;
    private:
        vector<synapse> incoming_synapse;
        vector<synapse> outgoing_synapse;
    public:
        neuron();

        explicit neuron(string id);

        virtual vector<synapse> getIncoming_synapse();

        bool operator==(neuron rhs);

        bool operator!=(neuron rhs);

        virtual void setIncomingSynapse(vector<synapse> incoming_synapse);

        vector<synapse> &getOutgoingSynapse();

        void setOutgoingSynapse(vector<synapse> outgoing_synapse);

        double getValue();

        virtual void setValue(double value);

        string getId();

        void setId(string id);

        virtual double activationValue();

        virtual double activationPrimeValue();

        void addOutgoingSynapse(synapse *pSynapse);

        virtual void addIncomingSynapse(synapse *pSynapse);
    };

    class bias_neuron : public neuron {
    public:
        bias_neuron();

        explicit bias_neuron(string id);

        double activationValue() override;

        double activationPrimeValue() override;

        void setValue(double value) override;

        void setIncomingSynapse(vector<synapse> incoming_synapse) override;

        void addIncomingSynapse(synapse *pSynapse) override;

    };

    bias_neuron::bias_neuron() {
        this->value = 1;
    }

    void bias_neuron::setIncomingSynapse(vector<synapse> incoming_synapse) {

    }

    void bias_neuron::setValue(double value) {

    }

    double bias_neuron::activationPrimeValue() {
        return neuron::getValue();
    }

    double bias_neuron::activationValue() {
        return neuron::getValue();
    }

    bias_neuron::bias_neuron(string id) {
        this->id = id;
        cout << "BiasNeuron created with id " << id << endl;
    }

    void bias_neuron::addIncomingSynapse(synapse *pSynapse) {
    }

    neuron::neuron() {
    }

    vector<synapse> neuron::getIncoming_synapse() {
        return incoming_synapse;
    }

    void neuron::setIncomingSynapse(vector<synapse> incoming_synapse) {
        neuron::incoming_synapse = incoming_synapse;
    }

    vector<synapse> &neuron::getOutgoingSynapse() {
        return outgoing_synapse;
    }

    void neuron::setOutgoingSynapse(vector<synapse> outgoing_synapse) {
        neuron::outgoing_synapse = outgoing_synapse;
    }

    double neuron::getValue() {
        return value;
    }

    void neuron::setValue(double value) {
        neuron::value = value;
    }

    string neuron::getId() {
        return id;
    }

    void neuron::setId(string id) {
        neuron::id = id;
    }

    bool neuron::operator==(neuron rhs) {
        return id == rhs.id;
    }

    bool neuron::operator!=(neuron rhs) {
        return !(rhs == *this);
    }

    double neuron::activationPrimeValue() {
        if (!this->incoming_synapse.empty()) {
            return derivativeSigmoid(value);
        } else {
            return value;
        }
    }

    double neuron::activationValue() {
        if (!this->incoming_synapse.empty()) {
            return sigmoid(value);
        } else {
            return value;
        }
    }

    neuron::neuron(string id) {
        this->id = id;
        cout << "Neuron created with id " << id << endl;
    }

    void neuron::addOutgoingSynapse(synapse *pSynapse) {
        this->outgoing_synapse.push_back(*pSynapse);
    }

    void neuron::addIncomingSynapse(synapse *pSynapse) {
        this->incoming_synapse.push_back(*pSynapse);
    }
}
#endif //NEURALNETWORK_NEURON_H
