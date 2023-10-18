package dbp._2.controller;

import dbp._2.entity.Student; // Student.java 경로
import dbp._2.service.StudentService; // StudentService 경로
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
    @GetMapping("/student/name/{name}") // name으로 검색
    public List<Student> findStudentByName(@PathVariable String name) {
        return studentService.findStudentByName(name);
    }

    @PutMapping("/update/{id}/{address}") // address 수정
    public String updateStudentAddress(@PathVariable Long id, @PathVariable
    String address) {
        studentService.updateStudentAddress(id, address);
        return "updated";
    }
    @DeleteMapping("/delete/{id}") // 데이터 삭제
    public String deleteStudentById(@PathVariable Long id) {
        studentService.deleteStudentById(id);
        return "deleted";
    }
    @PostMapping("/student/insert") // 데이터 삽입
    public String insertStudent(@RequestBody Student student) {
        studentService.insertStudent(student.getId(), student.getName(), student.getAddress(), student.getDept().getId());
        return "inserted";
    }
    @GetMapping("/student/all") // 전체 조회
    public List<Student> getAllStudents() {
        return studentService.getAllStudents();
    }
}


