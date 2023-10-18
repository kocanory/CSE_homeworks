package dbp.UnivJpql.controller;

import dbp.UnivJpql.entity.Student; // Student.java 경로
import dbp.UnivJpql.service.StudentService; // StudentService 경로
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.Optional;

@RestController
@RequestMapping("/")
public class StudentController {
    @Autowired
    StudentService studentService;

    @GetMapping("/student/id/{id}") // id로 검색
    public Optional<Student> findStudentById(@PathVariable Long id) {
        return studentService.findStudentById(id);
    }

}


