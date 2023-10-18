package dbp.UnivJpql.service;

import dbp.UnivJpql.entity.Student; // Student.java 경로
import dbp.UnivJpql.repository.StudentRepository; // StudentRepository.java 경로
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
}

