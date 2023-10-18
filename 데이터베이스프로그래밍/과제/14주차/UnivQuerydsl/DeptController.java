package dbp.UnivQuerydsl.controller;

import dbp.UnivQuerydsl.entity.Dept; // Dept.java 경로
import dbp.UnivQuerydsl.service.DeptService; // DeptService.java 경로
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;
import java.util.Optional;

@RestController
@RequestMapping("/dbp")
public class DeptController {
    @Autowired
    DeptService deptService;

    @GetMapping("/dept/name/{name}") // name으로 조회
    public Optional<Dept> findByDeptName(@PathVariable String name) {
        return deptService.findDeptByName(name);
    }
}