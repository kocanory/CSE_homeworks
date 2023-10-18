package dbp.UnivQuerydsl.controller;

import dbp.UnivQuerydsl.entity.Student; // Student.java 경로
import dbp.UnivQuerydsl.service.StudentService; // StudentService.java 경로
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.Optional;

@RestController
@RequestMapping("/")
public class StudentController {
    @Autowired
    StudentService studentService;

    @GetMapping("/student/id/{id}") // id로 조회
    public Optional<Student> findByStudentId(@PathVariable Long id) {
        return studentService.findStudentById(id);
    }
}