#ifndef MATRIX_
#define MATRIX_

#include <iostream>
#include <string>
#include <unordered_map>
// #include <exeption>
#include <vector>

namespace zich
{
    class Matrix
    {
        private:
            std::vector<double> matrix;
            int lines;
            int columns;
            /* data */
            
        public:
            // std::vector<double> matrix;
            // int lines;
            // int columns;
            Matrix(/* args */){

            }
            Matrix(/* args */ std::vector<double> mat,int lines,int columns){
                if((size_t)mat.size() != (size_t)(lines*columns)){
                    throw std::out_of_range{"The lines or columns or vector not in the right size!"};
                }
                this->matrix = mat;
                this->lines = lines;
                this->columns=columns;

            }

            Matrix operator+ (const Matrix &self) const;//V
            Matrix operator+= (Matrix &self); //V
            Matrix operator+ ()const;//V
            Matrix operator- (const Matrix &self) const;//V
            Matrix operator -= (Matrix &self);//V
            Matrix operator- ()const;//V 

            bool operator<(const Matrix & self)const;//V
            bool operator<=(const Matrix & self)const;//V
            bool operator>(const Matrix & self)const;//V
            bool operator>=(const Matrix & self)const;//V
            bool operator==(const Matrix & self)const;//V
            bool operator!=(const Matrix & self)const;//V

            Matrix & operator++();//V
            Matrix operator++(int needed);//V
            Matrix & operator--();//V
            Matrix operator--(int needed);//v

            Matrix operator*= (int num);//V
            Matrix operator* (int num);//V
            friend Matrix operator* (int num,const Matrix &mat);//V
            Matrix operator*= (const Matrix &mat);//V
            Matrix operator* (const Matrix &mat);
            friend Matrix operator*= (int num,Matrix &mat);//V
            friend std::ostream & operator << (std::ostream & os, const Matrix & self);//V
            friend std::istream & operator >> (std::istream & is, Matrix & self); // istream call to that operator it not object from our class so he need to be friend for private variable
            void matrix_size_exeption(const Matrix &mat,const Matrix &self) const;
            void matrix_size_exeption_multipication(const Matrix &mat,const Matrix &self) const;
            // void matrix_input_exeption(std::string &matend,int lines,int columns);
            ~Matrix(){
                //delete this->matrix; 
            }
    };
    
    
} // namespace ariel


#endif