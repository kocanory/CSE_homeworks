package dbp.UnivQuerydsl.service;

import dbp.UnivQuerydsl.entity.Dept; // Dept.java 경로
import dbp.UnivQuerydsl.repository.DeptRepository; // DeptRepository.java 경로
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Optional;

@Service
public class DeptService {
    @Autowired
    DeptRepository deptRepository;

    public Optional<Dept> findDeptByName(String name) {
        return deptRepository.findDeptByName(name);
    }
}