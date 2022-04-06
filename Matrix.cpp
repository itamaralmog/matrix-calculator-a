#include "Matrix.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstring>
#include <string>
using namespace zich;
using namespace std;

namespace zich{
    // void Matrix::matrix_input_exeption(std::string &matend,int lines,int columns){
    //     int sum_spaces = lines*(columns+2);
    //     int sum_psiks = lines-1;
    //     if(lines != (int)count(matend.begin(), matend.end(), ']')){
    //         throw std::out_of_range{"not in format"};
    //     }
    //     int sum_spaces_between = 0;
    //     for(unsigned long i=0; i < matend.size(); i++){
    //         if(matend[i] == ' '){
    //             sum_spaces--;
    //             sum_spaces_between++;
    //         }
    //         if(matend[i] == ','){
    //             sum_psiks--;
    //         }
    //         if(i != matend.size()-1 && matend[i] == ']' && matend[i+1] != ','){
    //             throw std::out_of_range{"not in format"};
    //         }
    //         if(matend[i] == ']'){
    //             if(sum_spaces_between != (columns+2)){
    //                 throw std::out_of_range{"not in format"};
    //             }
    //             sum_spaces_between = 0;
    //         }  
    //     }
    //     if(sum_spaces != 0 || sum_psiks !=0){
    //         throw std::out_of_range{"not in format"};
    //     }
    // }
    void Matrix::matrix_size_exeption(const Matrix &mat,const Matrix &self) const{
       if(mat.matrix.size() != self.matrix.size() || self.lines != mat.lines || self.columns != mat.columns){
            throw std::out_of_range{"matrix size exeption"};
        } 
    }

    void Matrix::matrix_size_exeption_multipication(const Matrix &mat,const Matrix &self) const{
       if(mat.columns!=self.lines){
            throw std::out_of_range{"matrix size multipication exeption"};
        } 
    }


    //function + binary matrix and matrix
    Matrix Matrix::operator+ (const Matrix &self) const
    {
        Matrix mat = *this;
        matrix_size_exeption(mat,self);
        vector<double> res;
        for(unsigned long i = 0; i < self.matrix.size(); i++){
            res.push_back(self.matrix.at(i)+mat.matrix.at(i));
        }
        Matrix result{res,self.lines,self.columns};
        return result;
    } 

    //function += binary matrix and matrix
    Matrix Matrix::operator+= (Matrix &self)
    {
        matrix_size_exeption(*this,self);
        for(unsigned long i = 0 ;i < this->matrix.size() ; i++)
        {
            this->matrix.at(i)+=self.matrix.at(i);
        }
        return *this;
    }
    //function + unary
    Matrix Matrix::operator+()const
    {
        Matrix mat = *this;
        return mat;
    }

    //function - binary matrix and matrix
    Matrix Matrix::operator- (const Matrix &self) const
    {

        Matrix mat = *this;
        matrix_size_exeption(mat,self);
        vector<double> res;
        for(unsigned long i = 0; i < self.matrix.size(); i++){
            res.push_back(mat.matrix.at(i)-self.matrix.at(i));
        }
        Matrix result{res,self.lines,self.columns};
        return result;
    } 
    //function -= binary
    Matrix Matrix::operator-= (Matrix &self)
    {
        matrix_size_exeption(*this,self);
        for(unsigned long i = 0 ;i < this->matrix.size() ; i++)
        {
            this->matrix.at(i)-=self.matrix.at(i);
        }
        return *this;
    }
    //function - unary
    Matrix Matrix::operator-()const
    {
        Matrix mat = *this;
        for(int i = 0 ;i < mat.lines*mat.columns; i++)
        {
            mat.matrix.at((unsigned long)i) = -mat.matrix.at((unsigned long)i);
        }
        return mat;
    }
    //function < binary
    bool Matrix::operator<(const Matrix & self)const{
        Matrix mat = *this;
        matrix_size_exeption(mat,self);
        double sum_mat=0;
        double sum_self=0;
        for(unsigned long  i = 0 ; i < mat.matrix.size(); ++i){
           sum_mat +=mat.matrix.at(i);
           sum_self +=self.matrix.at(i);
        }
        return sum_mat<sum_self;
    }
    //function <= binary
    bool Matrix::operator<=(const Matrix & self)const{
        Matrix mat = *this;
        matrix_size_exeption(mat,self);
        return (mat < self) || (mat == self);
    }
    //function > binary
    bool Matrix::operator>(const Matrix & self)const{
        Matrix mat = *this;
        matrix_size_exeption(mat,self);
        double sum_mat=0;
        double sum_self=0;
        for(unsigned long  i = 0 ; i < mat.matrix.size(); ++i){
           sum_mat +=mat.matrix.at(i);
           sum_self +=self.matrix.at(i);
        }
        return !((mat < self) || (mat == self));
    }
    //function >= binary
    bool Matrix::operator>=(const Matrix & self)const{
        Matrix mat = *this;
        matrix_size_exeption(mat,self);
        return(mat > self) || (mat == self);
    }
    //function == binary
    bool Matrix::operator==(const Matrix & self)const{
        Matrix mat = *this;
        matrix_size_exeption(mat,self);
        for(unsigned long  i = 0 ; i < mat.matrix.size(); ++i){
            if(mat.matrix.at(i) != self.matrix.at(i)){
                return false;
            }
        }
        return true;
    }
    //function != binary
    bool Matrix::operator!=(const Matrix & self)const{
        Matrix mat = *this;
        matrix_size_exeption(mat,self);
        return !(mat == self);
    }
    //function ++ before
    Matrix & Matrix::operator++(){ //++a
        for(unsigned long i = 0 ; i < this->matrix.size();++i){
            this->matrix.at(i)+=1;
        }
        return *this;
    }
    //function ++ after
    Matrix Matrix::operator++(int needed){//a++
       Matrix mat = *this;
       for(unsigned long i = 0 ; i < mat.matrix.size();++i){
            this->matrix.at(i)+=1;
        }
        return *this; 
    }
    //function -- before
    Matrix & Matrix::operator--(){
        for(unsigned long i = 0 ; i < this->matrix.size();++i){
            this->matrix.at(i)-=1;
        }
        return *this;
    }
    //function -- after
    Matrix Matrix::operator--(int needed){
       Matrix mat = *this;
       for(unsigned long i = 0 ; i < mat.matrix.size();++i){
            this->matrix.at(i)-=1;
        }
        return *this;  
    }
    //function *= matrix and than int
    Matrix Matrix::operator *= (int num)
    {
        double n = (double)num;
        for(unsigned long i = 0 ;i < this->matrix.size() ; i++)
        {
            this->matrix.at(i)= (double)this->matrix.at(i)*n;
        }
        return *this;
    }
    //function * matrix and than int
    Matrix Matrix::operator * (int num)
    {
        double n = (double)num;
        vector<double> new_mat;
        for(unsigned long i = 0 ;i < this->matrix.size() ; i++)
        {
            new_mat.push_back((double)this->matrix.at(i)*n);
        }
        Matrix result{new_mat,this->lines,this->columns};
        return result;
    }
    //function *= matrix and matrix
    Matrix Matrix::operator *=(const Matrix &mat1)
    {

        Matrix mat = *this;
        matrix_size_exeption_multipication(mat,mat1);
        vector<double> new_mat;
        unsigned long place = 0;  
        for(unsigned long i = 0 ; i < mat.lines; i++){
            for(unsigned long j = 0; j < mat1.columns ; j++){
                new_mat.push_back(0);       
                for(unsigned long k = 0; k < mat1.lines; k++){
                    if(mat.lines > mat.columns){
                        new_mat.at(place)+= mat.matrix.at(i*(unsigned long)mat.columns+k)*mat1.matrix.at(k*(unsigned long)mat1.lines+j);
                    }
                    else{
                        new_mat.at(place)+= mat.matrix.at(i*(unsigned long)mat.lines+k)*mat1.matrix.at(k*(unsigned long)mat1.columns+j); 
                    }
                }
                place++;
            }
        }
        this->matrix = new_mat;
        this->columns = mat1.columns;;
        return mat;
    }
    //function * matrix and matrix
    Matrix Matrix::operator * (const Matrix &mat1)
    {

        Matrix mat = *this;
        matrix_size_exeption_multipication(mat,mat1);
        vector<double> new_mat;
        unsigned long place = 0;     
        for(unsigned long i = 0 ; i < mat.lines; i++){
            for(unsigned long j = 0; j < mat1.columns ; j++){
                new_mat.push_back(0);       
                for(unsigned long k = 0; k < mat1.lines; k++){
                    if(mat.lines > mat.columns){
                        new_mat.at(place)+= mat.matrix.at(i*(unsigned long)mat.columns+k)*mat1.matrix.at(k*(unsigned long)mat1.lines+j);
                    }
                    else{
                       new_mat.at(place)+= mat.matrix.at(i*(unsigned long)mat.lines+k)*mat1.matrix.at(k*(unsigned long)mat1.columns+j); 
                    }
                }
                place++;
            }
        }
        Matrix result{new_mat,mat.lines,mat1.columns};
        return result;
    }
    //function * int and than matrix
    Matrix operator * ( int num ,const Matrix &mat)
    {
        double n = (double)num;
        vector<double> res;
        for(unsigned long i = 0 ;i < mat.matrix.size() ; i++)
        {
            res.push_back((double)mat.matrix.at((unsigned long)i)*n);
        }
        Matrix result{res,mat.lines,mat.columns};
        return result;
    }
    //function *= int and than matrix
    Matrix operator *= ( int num ,Matrix &mat)
    {
        double n = (double)num;
        vector<double> res;
        for(unsigned long i = 0 ;i < mat.matrix.size() ; i++)
        {
            res.push_back((double)mat.matrix.at((unsigned long)i)*n);
        }
        mat.matrix = res;
        return mat;
    }

    ostream & operator << (ostream & os, const Matrix &self)
    {
        string result;
        for(int i = 0 ; i < self.lines ; i++){
            result += "[ ";
            for(int j = 0 ; j < self.columns ; j++){
                int place = i*self.columns+j;
                result += to_string((int)self.matrix.at((unsigned long)place)); //(int) erase in the end.
                if(j != self.columns -1){
                    result += " ";
                }
            }
            if(i != self.lines -1){
                    result += " ]\n";
            }
            else{
                result += " ]";
            }
        }
        os << result;
        return os;
    }
    istream & operator >> (std::istream & is, Matrix & self){
        string element;
        string matend;
        int columns = -2;
        int lines = 0;
        vector<double> matrix;
        while(!is.eof()){
            is >> element;
            matend+=" "+element;
        }

        lines = (int)count(matend.begin(), matend.end(), '[');

        for(unsigned long i=0; i < matend.size(); i++){
            if(matend[i] == ' '){
                columns++;
            }
            if(matend[i] == ']'){
                break;
            }
        }

        // matrix_input_exeption(&matend,lines,columns);

        int sum_spaces = lines*(columns+2);
        int sum_psiks = lines-1;
        if(lines != (int)count(matend.begin(), matend.end(), ']')){
            throw std::out_of_range{"not in format"};
        }
        int sum_spaces_between = 0;
        for(unsigned long i=0; i < matend.size(); i++){
            if(matend[i] == ' '){
                sum_spaces--;
                sum_spaces_between++;
            }
            if(matend[i] == ','){
                sum_psiks--;
            }
            if(i != matend.size()-1 && matend[i] == ']' && matend[i+1] != ','){
                throw std::out_of_range{"not in format"};
            }
            if(matend[i] == ']'){
                if(sum_spaces_between != (columns+2)){
                    throw std::out_of_range{"not in format"};
                }
                sum_spaces_between = 0;
            }  
        }
        if(sum_spaces != 0 || sum_psiks !=0){
            throw std::out_of_range{"not in format"};
        }

        replace(matend.begin(),matend.end(),'[', ' ');
        replace(matend.begin(),matend.end(),']', ' ');
        replace(matend.begin(),matend.end(),',', ' ');

        string num_in_matrix;
        stringstream stream_matrix(matend);
        while (getline(stream_matrix, num_in_matrix,' ')) {
            if( num_in_matrix != "\0"){
                try{
                    double num_double =stod(num_in_matrix);
                    matrix.push_back(num_double);
                }
                catch (exception& ex) {
                    throw std::out_of_range{"not number"};
                }
            }
        }
        self.columns = columns;
        self.lines = lines;
        self.matrix = matrix;
        return is;
    }   
}


