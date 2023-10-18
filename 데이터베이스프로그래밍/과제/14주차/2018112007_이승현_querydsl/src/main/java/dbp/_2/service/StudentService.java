package dbp._2.service;

import dbp._2.entity.Student; // Student.java 경로
import dbp._2.repository.StudentRepository; // StudentRepository.java 경로
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Optional;

@Service
public class StudentService {
    @Autowired
    StudentRepository studentRepository;

    public Optional<Student> findStudentById(Long id) {
        return studentRepository.findStudentById(id);
    }
    public List<Student> findStudentByName(String name) {
        return studentRepository.findStudentByName(name);
    }
    public void updateStudentAddress(Long id, String address) {
        studentRepository.updateStudentAddress(id, address);
    }
    public void deleteStudentById(Long id) {
        studentRepository.deleteStudentById(id);
    }
    public List<Student> addStudents(List<Student> students){
        return studentRepository.saveAll(students);
    }
    public List<Student> getAllStudents(){
        return studentRepository.getAllStudents();
    }
}

